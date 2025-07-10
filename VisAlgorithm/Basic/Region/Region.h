#pragma once

#include "VisAlgorithmDefs.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionImpl;
using RegionImplPtr = std::shared_ptr<RegionImpl>;

class Region
{
public:
	Region();
	Region(double row1, double column1, double row2, double column2);
	Region(double row, double column, double radius);
	int64_t AreaCenter(double* row, double* column) const;

#ifdef VISALGORITHM_EXPORTS
	RegionImplPtr ImplPtr() const;
#endif
private:
	RegionImplPtr regionImpl_;
};

VISALGORITHM_NAMESPACE_END

