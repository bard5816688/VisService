#pragma once
#include "Contour.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>::ContourContext()
{

}

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>::~ContourContext()
{

}

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>::ContourContext(const ContourContext<Strategy>& other)
	: strategy_(other.strategy_)
{

}

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>& ContourContext<Strategy>::operator=(const ContourContext<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>::ContourContext(ContourContext&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsContourStrategy Strategy>
inline ContourContext<Strategy>& ContourContext<Strategy>::operator=(ContourContext<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsContourStrategy Strategy>
inline Strategy::Impl* ContourContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

VISALGORITHM_NAMESPACE_END