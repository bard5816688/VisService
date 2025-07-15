#pragma once

#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsTupleStrategy Strategy>
TupleContext<Strategy> TupleContext<Strategy>::FromVector(const std::vector<TupleElement>& values)
{
	return Strategy::FromVector(values);
}

template<IsTupleStrategy Strategy>
TupleContext<Strategy>::TupleContext()
{
	
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(const TupleElement& element)
{
	strategy_.Append(element);
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::~TupleContext()
{

}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(const TupleContext<Strategy>& other) 
	: strategy_(other.strategy_)
{

}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>& TupleContext<Strategy>::operator=(const TupleContext<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(TupleContext&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>& TupleContext<Strategy>::operator=(TupleContext<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsTupleStrategy Strategy>
inline Strategy::Impl* TupleContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

template<IsTupleStrategy Strategy>
TupleContext<Strategy>& TupleContext<Strategy>::Append(const TupleContext<Strategy>& tuple)
{
	strategy_.Append(tuple.strategy_);
	return *this;
}

template<IsTupleStrategy Strategy>
Result<TupleElementType> TupleContext<Strategy>::Type(size_t idx)
{
	return strategy_.Type(idx);
}

template<IsTupleStrategy Strategy>
Result<TupleElement> TupleContext<Strategy>::At(size_t idx) const
{
	return strategy_.At(idx);
}

VISALGORITHM_NAMESPACE_END