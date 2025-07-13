#pragma once

#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
	requires std::is_arithmetic_v<T> || std::is_same_v<T, std::string>
inline Result<T> Tuple::Get(size_t idx) const
{
	auto elemRes = At(idx);
	if (!elemRes) return tl::unexpected(elemRes.error());
	return std::get<T>(elemRes);
}

VISALGORITHM_NAMESPACE_END