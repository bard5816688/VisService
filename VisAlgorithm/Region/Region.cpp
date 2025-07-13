#include "RegionInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionImpl
{
public:
	HalconCpp::HRegion hRegion_;//底层也可以替换为VisRegion(自定义/其他Dll提供的Region类型)   
};

Region::Region()
	: regionImpl_(new RegionImpl)
{
	regionImpl_->hRegion_.GenEmptyObj();
}

Region::Region(double row1, double column1, double row2, double column2)
	: regionImpl_(new RegionImpl)
{
	regionImpl_->hRegion_.GenRectangle1(row1, column1, row2, column2);
}

Region::Region(double row, double column, double radius)
	: regionImpl_(new RegionImpl)
{
	regionImpl_->hRegion_.GenCircle(row, column, radius);
}

Region::~Region()
{
	delete regionImpl_;
}

Region::Region(const Region& other)
{
	regionImpl_ = new RegionImpl(*other.regionImpl_);
}

Region& Region::operator=(const Region& other)
{
	if (this != &other)
	{
		delete regionImpl_;
		regionImpl_ = new RegionImpl(*other.regionImpl_);
	}
	return *this;
}

Region::Region(Region&& other) noexcept
{
	regionImpl_ = other.regionImpl_;
	other.regionImpl_ = nullptr;
}

Region& Region::operator=(Region&& other) noexcept
{
	if (this != &other)
	{
		delete regionImpl_;
		regionImpl_ = other.regionImpl_;
		other.regionImpl_ = nullptr;
	}
	return *this;
}

int64_t Region::AreaCenter(double* row, double* column) const
{
	return regionImpl_->hRegion_.AreaCenter(row, column);
}

RegionImpl* Region::ImplPtr() const
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