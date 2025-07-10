#include "HRegion.h"
#include "HalconCpp.h"

VISALGORITHM_NAMESPACE_BEGIN

HRegion::HRegion()
{
	hRegion_ = std::make_shared<HalconCpp::HRegion>();
	hRegion_->GenEmptyRegion();
}

HRegion::HRegion(double row1, double column1, double row2, double column2)
{

}

HRegion::HRegion(double row, double column, double radius)
{

}

HRegion::~HRegion()
{
	
}

int64_t HRegion::AreaCenter(double* Row, double* Column) const
{
	return hRegion_->AreaCenter(Row, Column);
}

VISALGORITHM_NAMESPACE_END