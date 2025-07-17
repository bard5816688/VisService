#pragma once

#include "../Basic/BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
concept IsRegionStrategy = RuleOfFive<T> && requires(
	T t,
	const T & ct,
	double d,
	double* dPtr
	)
{
	{ ct.GetImpl() };
	{ t.GenRectangle1(d, d, d, d) }-> std::same_as<ResultVoid>;
	{ t.GenCircle(d, d, d) } -> std::same_as<ResultVoid>;
	{ ct.AreaCenter(dPtr, dPtr) }-> std::same_as<Result<int64_t>>;
};

VISALGORITHM_NAMESPACE_END
