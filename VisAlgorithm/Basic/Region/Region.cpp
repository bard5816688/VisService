#include "RegionInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionImpl
{
public:
	HalconCpp::HRegion hRegion_;//底层也可以替换为VisRegion(自定义/其他Dll提供的Region类型)   
};

Region::Region()
{
	regionImpl_->hRegion_.GenEmptyObj();
}

Region::Region(double row1, double column1, double row2, double column2)
{
	regionImpl_->hRegion_.GenRectangle1(row1, column1, row2, column2);
}

Region::Region(double row, double column, double radius)
{
	regionImpl_->hRegion_.GenCircle(row, column, radius);
}

int64_t Region::AreaCenter(double* row, double* column) const
{
	return regionImpl_->hRegion_.AreaCenter(row, column);
}

RegionImplPtr Region::ImplPtr() const
{
	return regionImpl_;
}

HalconCpp::HRegion GetHRegion(const Region& region)
{
	return region.ImplPtr()->hRegion_;
}

Region FromHRegion(const HalconCpp::HRegion& hRegion)
{
	Region rgn;
	rgn.ImplPtr()->hRegion_ = hRegion;
	return rgn;
}

VISALGORITHM_NAMESPACE_END