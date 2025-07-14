#pragma once

#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsTupleStrategy Strategy>
Tuple<Strategy> Tuple<Strategy>::FromVector(const std::vector<TupleElement>& values)
{
	return Strategy::FromVector(values);
}

template<IsTupleStrategy Strategy>
Tuple<Strategy>::Tuple()
{
	
}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>::Tuple(const TupleElement& element)
{
	strategy_.Append(element);
}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>::~Tuple()
{

}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>::Tuple(const Tuple<Strategy>& other) 
	: strategy_(other.strategy_)
{

}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>& Tuple<Strategy>::operator=(const Tuple<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>::Tuple(Tuple&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsTupleStrategy Strategy>
inline Tuple<Strategy>& Tuple<Strategy>::operator=(Tuple<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsTupleStrategy Strategy>
Tuple<Strategy>& Tuple<Strategy>::Append(const Tuple<Strategy>& tuple)
{
	strategy_.Append(tuple.strategy_);
	return *this;
}

template<IsTupleStrategy Strategy>
Result<TupleElementType> Tuple<Strategy>::Type(size_t idx)
{
	return strategy_.Type(idx);
}

template<IsTupleStrategy Strategy>
Result<TupleElement> Tuple<Strategy>::At(size_t idx) const
{
	return strategy_.At(idx);
}

VISALGORITHM_NAMESPACE_END