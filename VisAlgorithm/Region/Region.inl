#pragma once
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsRegionStrategy Strategy>
RegionContext<Strategy>::RegionContext()
{

}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::~RegionContext()
{

}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::RegionContext(const RegionContext<Strategy>& other)
	: strategy_(other.strategy_)
{

}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>& RegionContext<Strategy>::operator=(const RegionContext<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::RegionContext(RegionContext&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>& RegionContext<Strategy>::operator=(RegionContext<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsRegionStrategy Strategy>
ResultVoid RegionContext<Strategy>::GenRectangle1(double row1, double column1, double row2, double column2)
{
	return strategy_.GenRectangle1(row1, column1, row2, column2);
}

template<IsRegionStrategy Strategy>
ResultVoid RegionContext<Strategy>::GenCircle(double row, double column, double radius)
{
	return strategy_.GenCircle(row, column, radius);
}

template<IsRegionStrategy Strategy>
Result<int64_t> RegionContext<Strategy>::AreaCenter(double* row, double* column) const
{
	return strategy_.AreaCenter(row, column);
}

template<IsRegionStrategy Strategy>
Strategy::Impl* RegionContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

VISALGORITHM_NAMESPACE_END