#include "HHomMat2DStrategy.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HHomMat2DStrategy::Impl
{
public:
    HalconCpp::HHomMat2D hHomMat2D_;
};

HHomMat2DStrategy::HHomMat2DStrategy()
	: impl_(new Impl)
{
}

HHomMat2DStrategy::~HHomMat2DStrategy()
{
    delete impl_;
}

HHomMat2DStrategy::HHomMat2DStrategy(const HHomMat2DStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HHomMat2DStrategy& HHomMat2DStrategy::operator=(const HHomMat2DStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HHomMat2DStrategy::HHomMat2DStrategy(HHomMat2DStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HHomMat2DStrategy& HHomMat2DStrategy::operator=(HHomMat2DStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

Result<HHomMat2DStrategy> HHomMat2DStrategy::HomMat2dTranslate(double tx, double ty) const
{
	auto hHomMat = VISALGORITHM_WRAP_TRY_CATCH(impl_->hHomMat2D_.HomMat2dTranslate(tx, ty));
	return hHomMat.transform([this](const HalconCpp::HHomMat2D& hHomMat)
		{
			this->impl_->hHomMat2D_ = hHomMat;
			return *this;
		});
}

VISALGORITHM_NAMESPACE_END