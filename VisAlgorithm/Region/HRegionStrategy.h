#pragma once

#include "RegionStrategyConcept.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class VisAlgorithmApi HRegionStrategy
{
public:
	class Impl;
	HRegionStrategy();
	~HRegionStrategy();
	HRegionStrategy(const HRegionStrategy& other);
	HRegionStrategy& operator=(const HRegionStrategy& other);
	HRegionStrategy(HRegionStrategy&& other) noexcept;
	HRegionStrategy& operator=(HRegionStrategy&& other) noexcept;

	ResultVoid GenRectangle1(double row1, double column1, double row2, double column2);
	ResultVoid GenCircle(double row, double column, double radius);
	Result<int64_t> AreaCenter(double* row, double* column) const;

public:
	Impl* GetImpl() const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif