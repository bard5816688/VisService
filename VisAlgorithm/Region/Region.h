#pragma once
#include "HRegionStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

#ifdef USE_HALCON
template<IsRegionStrategy Strategy = HRegionStrategy>
#else
template<IsRegionStrategy Strategy>
#endif
class RegionContext
{
public:
	RegionContext();
	~RegionContext();
	RegionContext(const RegionContext& other);
	RegionContext& operator=(const RegionContext& other);
	RegionContext(RegionContext&& other) noexcept;
	RegionContext& operator=(RegionContext&& other) noexcept;

	ResultVoid GenRectangle1(double row1, double column1, double row2, double column2);
	ResultVoid GenCircle(double row, double column, double radius);
	Result<int64_t> AreaCenter(double* row, double* column) const;

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