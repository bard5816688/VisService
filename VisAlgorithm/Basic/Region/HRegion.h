#pragma once
#include "VisAlgorithmDefs.h"
#include "Tuple.h"

namespace HalconCpp
{
	class HRegion;
}

VISALGORITHM_NAMESPACE_BEGIN

class HRegion
{
public:
	HRegion();
	HRegion(double row1, double column1, double row2, double column2);
	HRegion(double row, double column, double radius);
	virtual ~HRegion();
	int64_t AreaCenter(double* Row, double* Column) const;

protected:
	HRegionInstancePtr hRegion_;
};

using HRegionInstancePtr = std::shared_ptr <HalconCpp::HRegion>;

VISALGORITHM_NAMESPACE_END
