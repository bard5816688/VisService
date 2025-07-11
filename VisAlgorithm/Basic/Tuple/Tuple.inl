#pragma once

#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
	requires std::is_arithmetic_v<T> || std::is_same_v<T, std::string>
inline T Tuple::Get(size_t index) const
{
	return std::get<T>(At(index));
}

VISALGORITHM_NAMESPACE_END