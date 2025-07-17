#pragma once

#include "../Basic/BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
concept IsContourStrategy = RuleOfFive<T> && requires(
	T t,
	const T & ct
	)
{
	{ ct.GetImpl() } -> std::convertible_to<void*>;
};

VISALGORITHM_NAMESPACE_END

