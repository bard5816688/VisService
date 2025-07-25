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
concept ReflectableStruct = requires {{ Reflectable<T>::getMembers() }; };

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
			{ ((names.push_back(m.name_)), ...); }, members);
		return names;
	}

	// 获取字段类型名
	static std::optional<std::string_view> getTypeNameByField(std::string_view name)
	{
		auto members = getMembers();
		std::optional<std::string_view> result;

		std::apply([&](auto&&... m) {
			(([&] {
				if (m.name_ == name) {
					result = m.typeName_;
				}
				}()), ...);
			}, members);

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
	static bool setFieldByName(T& obj, std::string_view name, const FieldT& value) {
		auto members = getMembers();
		bool success = false;
		std::apply([&](auto&&... m) {
			((m.name_ == name
				? ([&]() {
					using MemberT = std::decay_t<decltype(obj.*(m.ptr_))>;
					if constexpr (std::is_same_v<FieldT, MemberT>) {
						obj.*(m.ptr_) = value;
						success = true;
					}
					}(), true)
				: false), ...);
			}, members);
		return success;
	}


	// 类型安全 get 接口
	template <typename FieldT>
	static std::optional<FieldT> getFieldByName(const T& obj, std::string_view name) {
		auto members = getMembers();
		std::optional<FieldT> result;
		std::apply([&](auto&&... m) {
			((m.name_ == name
				? ([&]() {
					using MemberT = std::decay_t<decltype(obj.*(m.ptr_))>;
					if constexpr (std::is_same_v<FieldT, MemberT>) {
						result = obj.*(m.ptr_);
					}
					}(), true)
				: false), ...);
			}, members);
		return result;
	}


private:
	template <std::size_t... I>
	static void* getMemberPointerImpl(T* obj, std::string_view name,
		const auto& members, std::index_sequence<I...>)
	{
		void* result = nullptr;

		(..., ([&] {
			const auto& member = std::get<I>(members);
			if (member.name_ == name) {
				result = static_cast<void*>(&(obj->*(member.ptr_)));
			}
			}()));

		return result;
	}

};

VISSERVICE_NAMESPACE_END

#define REFLECT_STRUCT(StructType, ...)                             \
template <>                                                         \
struct Reflectable<StructType> {                                    \
    using T = StructType;                                           \
    static constexpr auto getMembers() {                            \
        return std::make_tuple(                                     \
            MAKE_MEMBER_INFO(T, __VA_ARGS__)                        \
        );                                                          \
    }                                                               \
};

#define MAKE_MEMBER_INFO(T, ...)                                     \
    MAKE_MEMBER_INFO_IMPL(T, __VA_ARGS__)

#define MAKE_MEMBER_INFO_IMPL(T, ...)                                \
    std::make_tuple(__VA_ARGS__)

#define MEMBER(field)                                                \
    MemberInfo<T, decltype(T::field)>{#field, &T::field}

/*
VISSERVICE_NAMESPACE_BEGIN

struct Person {
	std::string name;
	int age;
};

REFLECT_STRUCT(Person,
	MEMBER(name),
	MEMBER(age)
)

VISSERVICE_NAMESPACE_END
*/