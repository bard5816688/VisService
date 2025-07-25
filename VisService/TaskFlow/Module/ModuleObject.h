#pragma once
#include <tuple>
#include <string_view>
#include <vector>
#include <optional>
#include <type_traits>
#include <typeinfo>
#include "../../Basic/BasicObject.h"

VISSERVICE_NAMESPACE_BEGIN

template <typename T>
struct Reflectable;

template <typename T>
concept ReflectableStruct = requires {
	{ Reflectable<T>::getMembers() };
};

template <typename T, typename MemberT>
struct MemberInfo
{
    std::string_view name_;
    MemberT T::* ptr_;
    std::string_view typeName_;

    constexpr MemberInfo(std::string_view n, MemberT T::* p)
        : name_(n)
        , ptr_(p)
        , typeName_(typeid(MemberT).name())
    {
    }
};

template <ReflectableStruct T>
struct ReflectStruct
{
    static constexpr auto getMembers()
    {
        return Reflectable<T>::getMembers();
    }

    static constexpr std::size_t memberCount()
    {
        return std::tuple_size_v<decltype(getMembers())>;
    }

    template <std::size_t I>
    static constexpr auto getMemberInfo()
    {
        return std::get<I>(getMembers());
    }

    // 获取字段名列表
    static std::vector<std::string_view> getMemberNames()
    {
        auto members = getMembers();
        std::vector<std::string_view> names;
        std::apply([&](auto &&...m)
            { ((names.push_back(m.name)), ...); }, members);
        return names;
    }

    // 获取字段类型名
    static std::optional<std::string_view> getTypeNameByField(std::string_view name)
    {
        auto members = getMembers();
        std::optional<std::string_view> result;
        std::apply([&](auto &&...m)
            { ((m.name == name ? result = m.type_name : void()), ...); }, members);
        return result;
    }

    // 获取字段指针（void*）
    static void* getMemberPointerByName(T* obj, std::string_view name)
    {
        auto members = getMembers();
        return getMemberPointerImpl(obj, name, members, std::make_index_sequence<std::tuple_size_v<decltype(members)>>{});
    }

    // 类型安全 set 接口
    template <typename FieldT>
    static bool setFieldByName(T& obj, std::string_view name, const FieldT& value)
    {
        auto members = getMembers();
        bool success = false;
        std::apply([&](auto &&...m)
            { ((m.name == name &&
                std::is_same_v<FieldT, std::decay_t<decltype(obj.*(m.ptr))>>
                ? ((obj.*(m.ptr) = value), success = true)
                : void()),
                ...); }, members);
        return success;
    }

    // 类型安全 get 接口
    template <typename FieldT>
    static std::optional<FieldT> getFieldByName(const T& obj, std::string_view name)
    {
        auto members = getMembers();
        std::optional<FieldT> result;
        std::apply([&](auto &&...m)
            { ((m.name == name &&
                std::is_same_v<FieldT, std::decay_t<decltype(obj.*(m.ptr))>>
                ? result = obj.*(m.ptr)
                : void()),
                ...); }, members);
        return result;
    }

private:
    template <std::size_t... I>
    static void* getMemberPointerImpl(T* obj, std::string_view name,
        const auto& members, std::index_sequence<I...>)
    {
        void* result = nullptr;
        (..., (members[I].name == name ? result = static_cast<void*>(&(obj->*members[I].ptr)) : void()));
        return result;
    }
};

VISSERVICE_NAMESPACE_END