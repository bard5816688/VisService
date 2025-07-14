#include "RegionInternal.h"
#include "BasicReturnInternal.h"

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

ResultVoid Region::GenRectangle1(double row1, double column1, double row2, double column2)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rect1, regionImpl_->hRegion_.GenRectangle1(row1, column1, row2, column2));
	return rect1;
}

ResultVoid Region::GenCircle(double row, double column, double radius)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(circle, regionImpl_->hRegion_.GenCircle(row, column, radius));
	return circle;
}

Result<int64_t> Region::AreaCenter(double* row, double* column) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(area, regionImpl_->hRegion_.AreaCenter(row, column));
	return area;
}

HalconCpp::HRegion RegionInternal::GetHRegion(const Region& region)
{
	return region.regionImpl_->hRegion_;
}

Region RegionInternal::FromHRegion(const HalconCpp::HRegion& hRegion)
{
	Region rgn;
	rgn.regionImpl_->hRegion_ = hRegion;
	return rgn;
}

Result<Region> RegionInternal::ResultFromHRegion(const Result<HalconCpp::HRegion>& result)
{
	return result.transform(FromHRegion);
}

VISALGORITHM_NAMESPACE_END