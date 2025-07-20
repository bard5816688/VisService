#pragma once
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::RegionContext()
{

}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::~RegionContext()
{

}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::RegionContext(const Strategy& strategy)
	: strategy_(strategy_)
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
	if (this != &other)
	{
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>::RegionContext(RegionContext<Strategy>&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsRegionStrategy Strategy>
inline RegionContext<Strategy>& RegionContext<Strategy>::operator=(RegionContext<Strategy>&& other) noexcept
{
	if (this != &other)
	{
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
ResultVoid RegionContext<Strategy>::GenRectangle2(double row, double column, double phi, double length1, double length2)
{
	return strategy_.GenRectangle2(row, column, phi, length1, length2);
}

template<IsRegionStrategy Strategy>
ResultVoid RegionContext<Strategy>::GenCircle(double row, double column, double radius)
{
	return strategy_.GenCircle(row, column, radius);
}

template<IsRegionStrategy Strategy>
ResultVoid RegionContext<Strategy>::GenEllipse(double row, double column, double phi, double radius1, double radius2)
{
	return strategy_.GenEllipse(row, column, phi, radius1, radius2);
}

template<IsRegionStrategy Strategy>
Result<int64_t> RegionContext<Strategy>::AreaCenter(double* row, double* column) const
{
	return strategy_.AreaCenter(row, column);
}

template<IsRegionStrategy Strategy>
ResultVoid RegionContext<Strategy>::SmallestRectangle2(double* row, double* column, double* phi, double* length1, double* length2) const
{
	return strategy_.SmallestRectangle2(row, column, phi, length1, length2);
}

template<IsRegionStrategy Strategy>
Result<double> RegionContext<Strategy>::Convexity() const
{
	return strategy_.Convexity();
}

template<IsRegionStrategy Strategy>
Result<double> RegionContext<Strategy>::Circularity() const
{
	return strategy_.Circularity();
}

template<IsRegionStrategy Strategy>
Result<int64_t>  RegionContext<Strategy>::ConnectAndHoles(int64_t numholes) const
{
	return strategy_.ConnectAndHoles(numholes);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::Union1() const
{
	return strategy_.Union1();
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::Intersection(const RegionContext<Strategy>& region2)const
{
	return strategy_.Intersection(region2);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::Difference(const RegionContext<Strategy>& sub) const
{
	return strategy_.Difference(sub);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::SelectShape(const char* features, const char* operation, double min, double max) const
{
	return strategy_.SelectShape(features, operation, min, max);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::Connection() const
{
	return strategy_.Connection();
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::Dilation1(const RegionContext<Strategy>& structElement, int64_t iterations) const
{
	return strategy_.Dilation1(structElement, iterations);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::HoughCircles(int64_t radius, int64_t percent, int64_t mode) const
{
	return strategy_.HoughCircles(radius, percent, mode);
}

template<IsRegionStrategy Strategy>
Result<RegionContext<Strategy>> RegionContext<Strategy>::ShapeTrans(const char* type) const
{
	return strategy_.ShapeTrans(type);
}

template<IsRegionStrategy Strategy>
Strategy::Impl* RegionContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

VISALGORITHM_NAMESPACE_END