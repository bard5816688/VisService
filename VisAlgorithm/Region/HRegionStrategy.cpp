#include "../Region/RegionInternal.h"
#include "../Basic/BasicReturnInternal.h"
#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class HRegionStrategy::Impl
{
public:
	HalconCpp::HRegion& GetHobj()
	{
		return hRegion_;
	}

	static HRegionStrategy FromHRegion(const HalconCpp::HRegion& hRegion)
	{
		HRegionStrategy hRegionStrategy;
		hRegionStrategy.impl_->hRegion_ = hRegion;
		return hRegionStrategy;
	}

	static Result<HRegionStrategy> ResultFromHRegion(const Result<HalconCpp::HRegion>& result)
	{
		return result.transform(HRegionStrategy::Impl::FromHRegion);
	}

private:
	HalconCpp::HRegion hRegion_;
};

HRegionStrategy::HRegionStrategy()
	: impl_(new Impl)
{
	impl_->GetHobj().GenEmptyObj();
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
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rect1, impl_->GetHobj().GenRectangle1(row1, column1, row2, column2));
	return rect1;
}

ResultVoid HRegionStrategy::GenCircle(double row, double column, double radius)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(circle, impl_->GetHobj().GenCircle(row, column, radius));
	return circle;
}

Result<int64_t> HRegionStrategy::AreaCenter(double* row, double* column) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(area, impl_->GetHobj().AreaCenter(row, column));
	return area;
}

ResultVoid HRegionStrategy::GenRectangle2(double row, double column, double phi, double length1, double length2)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rect2, impl_->GetHobj().GenRectangle2(row, column, phi, length1, length2));
	return rect2;
}

ResultVoid HRegionStrategy::GenEllipse(double row, double column, double phi, double radius1, double radius2)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(elli, impl_->GetHobj().GenEllipse(row, column, phi, radius1, radius2));
	return elli;
}

ResultVoid HRegionStrategy::SmallestRectangle2(double* row, double* column, double* phi, double* length1, double* length2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(smallrect, impl_->GetHobj().SmallestRectangle2(row, column, phi, length1, length2));
	return smallrect;
}

Result<double> HRegionStrategy::Convexity() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(vexity, impl_->GetHobj().Convexity());
	return vexity;
}

Result<double> HRegionStrategy::Circularity() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(cularity, impl_->GetHobj().Circularity());
	return cularity;
}

Result<int64_t> HRegionStrategy::ConnectAndHoles(int64_t* numholes) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(ect, impl_->GetHobj().ConnectAndHoles(numholes));
	return ect;
}

Result<HRegionStrategy> HRegionStrategy::Union1() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rgn, impl_->GetHobj().Union1());
	return HRegionStrategy::Impl::ResultFromHRegion(rgn);
}

Result<HRegionStrategy> HRegionStrategy::Intersection(const HRegionStrategy& region2)const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rgn, impl_->GetHobj().Intersection(region2.impl_->GetHobj()));
	return HRegionStrategy::Impl::ResultFromHRegion(rgn);
}

Result<HRegionStrategy> HRegionStrategy::Difference(const HRegionStrategy& sub) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rgn, impl_->GetHobj().Difference(sub.impl_->GetHobj()));
	return HRegionStrategy::Impl::ResultFromHRegion(rgn);
}

Result<HRegionStrategy> HRegionStrategy::SelectShape(const char* features, const char* operation, double min_, double max_) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rgn, impl_->GetHobj().SelectShape(features, operation, min_, max_));
	return HRegionStrategy::Impl::ResultFromHRegion(rgn);
}

Result<HRegionStrategy> HRegionStrategy::Connection() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(rgn, impl_->GetHobj().Union1());
	return HRegionStrategy::Impl::ResultFromHRegion(rgn);
}

Result<HRegionStrategy> HRegionStrategy::Dilation1(const HRegionStrategy& structElement, int64_t iterations) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(dilat, impl_->GetHobj().Union1());
	return HRegionStrategy::Impl::ResultFromHRegion(dilat);
}

Result<HRegionStrategy> HRegionStrategy::HoughCircles(int64_t radius, int64_t percent, int64_t mode) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(cir, impl_->GetHobj().Union1());
	return HRegionStrategy::Impl::ResultFromHRegion(cir);
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