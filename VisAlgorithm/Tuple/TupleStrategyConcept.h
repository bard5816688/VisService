#pragma once

#include <variant>
#include <string>
#include "BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

using TupleElement = std::variant<std::monostate, int, double, std::string>;

enum class TupleElementType
{
	Null,
	Int,
	Double,
	String,
};

template<typename T>
concept IsTupleStrategy = RuleOfFive<T> && requires(
	T t,
	const std::vector<TupleElement>& vte,
	const T& ct,
	size_t size_t
	)
{
	{ T::FromVector(vte) }  -> std::same_as<T>;
	{ t.Append(ct) }  -> std::same_as<T&>;
	{ t.Type(size_t) }  -> std::same_as<Result<TupleElementType>>;
	{ t.At(size_t) }  -> std::same_as<Result<TupleElement>>;
};

VISALGORITHM_NAMESPACE_END