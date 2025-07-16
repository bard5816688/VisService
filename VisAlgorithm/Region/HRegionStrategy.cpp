#include "RegionInternal.h"
#include "BasicReturnInternal.h"
#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class HRegionStrategy::Impl
{
public:
	HalconCpp::HRegion& GetHobj()
	{
		return hRegion_;
	}

	HalconCpp::HRegion hRegion_;
};

HRegionStrategy::HRegionStrategy()
	: impl_(new Impl)
{
	impl_->hRegion_.GenEmptyObj();
}

HRegionStrategy::~HRegionStrategy()
{
	delete impl_;
}

HRegionStrategy::HRegionStrategy(const HRegionStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HRegionStrategy& HRegionStrategy::operator=(const HRegionStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HRegionStrategy::HRegionStrategy(HRegionStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HRegionStrategy& HRegionStrategy::operator=(HRegionStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

ResultVoid HRegionStrategy::GenRectangle1(double row1, double column1, double row2, double column2)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rect1, impl_->hRegion_.GenRectangle1(row1, column1, row2, column2));
	return rect1;
}

ResultVoid HRegionStrategy::GenCircle(double row, double column, double radius)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(circle, impl_->hRegion_.GenCircle(row, column, radius));
	return circle;
}

Result<int64_t> HRegionStrategy::AreaCenter(double* row, double* column) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(area, impl_->hRegion_.AreaCenter(row, column));
	return area;
}

HRegionStrategy::Impl* HRegionStrategy::GetImpl() const
{
	return impl_;
}


HalconCpp::HRegion RegionInternalUtils::GetHRegion(const Region& region)
{
	return region.GetImpl()->GetHobj();
}

Region RegionInternalUtils::FromHRegion(const HalconCpp::HRegion& hRegion)
{
	Region rgn;
	rgn.GetImpl()->GetHobj() = hRegion;
	return rgn;
}

Result<Region> RegionInternalUtils::ResultFromHRegion(const Result<HalconCpp::HRegion>& result)
{
	return result.transform(RegionInternalUtils::FromHRegion);
}

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON