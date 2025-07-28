#pragma once
#include <tuple>
#include <string>
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
	std::string name_;
	MemberT T::* ptr_;
	std::string typeName_;

	constexpr MemberInfo(std::string n, MemberT T::* p)
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

	static std::vector<std::string> getMemberNames()
	{
		auto members = getMembers();
		std::vector<std::string> names;
		std::apply([&](auto &&...m)
			{ ((names.push_back(m.name_)), ...); }, members);
		return names;
	}

	static std::optional<std::string> getTypeNameByField(std::string name)
	{
		auto members = getMembers();
		std::optional<std::string> result;

		std::apply([&](auto&&... m) {
			(([&] {
				if (m.name_ == name) {
					result = m.typeName_;
				}
				}()), ...);
			}, members);

		return result;
	}

	static void* getMemberPointerByName(T* obj, std::string name)
	{
		auto members = getMembers();
		return getMemberPointerImpl(obj, name, members, std::make_index_sequence<std::tuple_size_v<decltype(members)>>{});
	}

	template <typename FieldT>
	static bool setFieldByName(T& obj, std::string name, const FieldT& value) {
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


	template <typename FieldT>
	static std::optional<FieldT> getFieldByName(const T& obj, std::string name) {
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
	static void* getMemberPointerImpl(T* obj, std::string name,
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
            __VA_ARGS__                                             \
        );                                                          \
    }                                                               \
};

#define MEMBER(struct_type, field) \
    MemberInfo<struct_type, decltype(struct_type::field)>{ #struct_type "." #field, &struct_type::field }




/*
VISSERVICE_NAMESPACE_BEGIN

struct Person {
	std::string name;
	int age;
};

REFLECT_STRUCT(Person,
	MEMBER(Person, name),
	MEMBER(Person, age)
)

VISSERVICE_NAMESPACE_END
*/