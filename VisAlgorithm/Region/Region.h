#pragma once

#include "BasicReturn.h"
#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionImpl;

class VisAlgorithmApi Region
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
	RegionImpl* regionImpl_;

	friend class RegionInternal;
};

VISALGORITHM_NAMESPACE_END

