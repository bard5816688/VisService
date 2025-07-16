#include "ContourInternal.h"
#include "BasicReturnInternal.h"
#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class HContourStrategy::Impl
{
public:
	HalconCpp::HXLDCont& GetHobj()
	{
		return hXldCont_;
	}

	HalconCpp::HXLDCont hXldCont_;
};

HContourStrategy::HContourStrategy()
	: impl_(new Impl)
{
	impl_->hXldCont_.GenEmptyObj();
}

HContourStrategy::~HContourStrategy()
{
	delete impl_;
}

HContourStrategy::HContourStrategy(const HContourStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HContourStrategy& HContourStrategy::operator=(const HContourStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HContourStrategy::HContourStrategy(HContourStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HContourStrategy& HContourStrategy::operator=(HContourStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

HContourStrategy::Impl* HContourStrategy::GetImpl() const
{
	return impl_;
}


HalconCpp::HXLDCont ContourInternalUtils::GetHXldContour(const Contour& region)
{
	return region.GetImpl()->GetHobj();
}

Contour ContourInternalUtils::FromHXldContour(const HalconCpp::HXLDCont& hRegion)
{
	Contour cont;
	cont.GetImpl()->GetHobj() = hRegion;
	return cont;
}

Result<Contour> ContourInternalUtils::ResultFromHXldContour(const Result<HalconCpp::HXLDCont>& result)
{
	return result.transform(ContourInternalUtils::FromHXldContour);
}

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON
