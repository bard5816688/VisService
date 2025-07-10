#pragma once

#include "HRegion.h"
#include "VisRegion.h"

VISALGORITHM_NAMESPACE_BEGIN

class Region : public HRegion, public VisRegion
{
public:
	Region()
		: HRegion()
		, VisRegion()
	{

	}

	Region(double row1, double column1, double row2, double column2)
		: HRegion(row1, column1, row2, column2)
		, VisRegion(row1, column1, row2, column2)
	{

	}

	Region(double row, double column, double radius)
		: HRegion(row, column, radius)
		, VisRegion(row, column, radius)
	{

	}

	~Region()
	{

	}

#ifdef  VISALGORITHM_EXPORTS

	HRegionInstancePtr GetHRegionInstancePtr()
	{
		return hRegion_;
	}

#endif //  VISALGORITHM_EXPORTS
};

VISALGORITHM_NAMESPACE_END

