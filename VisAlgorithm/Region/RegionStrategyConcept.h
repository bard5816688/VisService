#pragma once

#include <variant>
#include <string>
#include "BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
concept IsRegionStrategy = RuleOfFive<T> && requires(
	T t,
	const T& ct,
	double d,
	double* pd
	)
{
	{ ct.GetImpl() };
	{ t.GenRectangle1(d, d, d, d) }-> std::same_as<ResultVoid>;
	{ t.GenCircle(d, d, d) } -> std::same_as<ResultVoid>;
	{ ct.AreaCenter(pd, pd) }-> std::same_as<Result<int64_t>>;
};

VISALGORITHM_NAMESPACE_END