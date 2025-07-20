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
	ResultVoid GenRectangle2(double row, double column, double phi, double length1, double length2);
	ResultVoid GenEllipse(double row, double column, double phi, double radius1, double radius2);
	ResultVoid SmallestRectangle2(double* row, double* column, double* phi, double* length1, double* length2) const;
	Result<double> Convexity() const;
	Result<double> Circularity() const;
	Result<int64_t> ConnectAndHoles(int64_t* numholes) const;
	Result<HRegionStrategy> Union1() const;
	Result<HRegionStrategy> Intersection(const HRegionStrategy& region2)const;
	Result<HRegionStrategy> Difference(const HRegionStrategy& sub) const;
	Result<HRegionStrategy> SelectShape(const char* features, const char* operation, double min_, double max_) const;
	Result<HRegionStrategy> Connection() const;
	Result<HRegionStrategy> Dilation1(const HRegionStrategy& structElement, int64_t iterations) const;
	Result<HRegionStrategy> HoughCircles(int64_t radius, int64_t percent, int64_t mode) const;

public:
	Impl* GetImpl() const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif