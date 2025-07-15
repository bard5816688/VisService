#pragma once
#include "HRegionStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

#ifdef USE_HALCON
template<IsRegionStrategy Strategy = HRegionStrategy>
#else
template<IsRegionStrategy Strategy>
#endif
class Region
{
public:
	Region();
	~Region();
	Region(const Region& other);
	Region& operator=(const Region& other);
	Region(Region&& other) noexcept;
	Region& operator=(Region&& other) noexcept;

	ResultVoid GenRectangle1(double row1, double column1, double row2, double column2);
	ResultVoid GenCircle(double row, double column, double radius);
	Result<int64_t> AreaCenter(double* row, double* column) const;

private:
	Strategy strategy_;
};

VISALGORITHM_NAMESPACE_END

#include"Region.inl"