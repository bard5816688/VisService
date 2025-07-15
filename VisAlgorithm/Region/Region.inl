#pragma once
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsRegionStrategy Strategy>
Region<Strategy>::Region()
{

}

template<IsRegionStrategy Strategy>
inline Region<Strategy>::~Region()
{

}

template<IsRegionStrategy Strategy>
inline Region<Strategy>::Region(const Region<Strategy>& other)
	: strategy_(other.strategy_)
{

}

template<IsRegionStrategy Strategy>
inline Region<Strategy>& Region<Strategy>::operator=(const Region<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsRegionStrategy Strategy>
inline Region<Strategy>::Region(Region&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsRegionStrategy Strategy>
inline Region<Strategy>& Region<Strategy>::operator=(Region<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsRegionStrategy Strategy>
ResultVoid Region<Strategy>::GenRectangle1(double row1, double column1, double row2, double column2)
{
	return strategy_.GenRectangle1(row1, column1, row2, column2);
}

template<IsRegionStrategy Strategy>
ResultVoid Region<Strategy>::GenCircle(double row, double column, double radius)
{
	return strategy_.GenCircle(row, column, radius);
}

template<IsRegionStrategy Strategy>
Result<int64_t> Region<Strategy>::AreaCenter(double* row, double* column) const
{
	return strategy_.AreaCenter(row, column);
}

VISALGORITHM_NAMESPACE_END