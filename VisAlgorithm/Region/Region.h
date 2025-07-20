#pragma once
#include "HRegionStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsRegionStrategy Strategy>
class RegionContext
{
public:
	RegionContext();
	~RegionContext();
	RegionContext(const Strategy& strategy);
	RegionContext(const RegionContext& other);
	RegionContext& operator=(const RegionContext& other);
	RegionContext(RegionContext&& other) noexcept;
	RegionContext& operator=(RegionContext&& other) noexcept;

	ResultVoid GenRectangle1(double row1, double column1, double row2, double column2);
	ResultVoid GenRectangle2(double row, double column, double phi, double length1, double length2);
	ResultVoid GenEllipse(double row, double column, double phi, double radius1, double radius2);
	ResultVoid GenCircle(double row, double column, double radius);
	Result<int64_t> AreaCenter(double* row, double* column) const;
	ResultVoid SmallestRectangle2(double* row, double* column, double* phi, double* length1, double* length2) const;
	Result<double> Convexity() const;
	Result<double> Circularity() const;
	Result<int64_t> ConnectAndHoles(int64_t numholes) const;
	Result<RegionContext> Union1() const;
	Result<RegionContext> Intersection(const RegionContext& region2)const;
	Result<RegionContext> Difference(const RegionContext& sub) const;
	Result<RegionContext> SelectShape(const char* features, const char* operation, double min, double max) const;
	Result<RegionContext> Connection() const;
	Result<RegionContext> Dilation1(const RegionContext& structElement, int64_t iterations) const;
	Result<RegionContext> HoughCircles(int64_t radius, int64_t percent, int64_t mode) const;
	Result<RegionContext> ShapeTrans(const char* type) const;

private:
	Strategy::Impl* GetImpl() const;
	Strategy strategy_;

	friend class RegionInternalUtils;
};

#ifdef USE_HALCON
#define DEFAULT_REGION_STRATEGY HRegionStrategy
#elif
#define DEFAULT_REGION_STRATEGY "NoSupported"
#endif
using Region = RegionContext<DEFAULT_REGION_STRATEGY>;

VISALGORITHM_NAMESPACE_END

#include"Region.inl"