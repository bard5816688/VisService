#include "HHomMat2DStrategy.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HHomMat2DStrategyImpl
{
public:
    HalconCpp::HHomMat2D hHomMat2D_;
};

HHomMat2DStrategy::HHomMat2DStrategy()
	: hHomMat2DStrategyImpl_(new HHomMat2DStrategyImpl)
{
}

HHomMat2DStrategy::~HHomMat2DStrategy()
{
    delete hHomMat2DStrategyImpl_;
}

HHomMat2DStrategy::HHomMat2DStrategy(const HHomMat2DStrategy& other)
{
	hHomMat2DStrategyImpl_ = new HHomMat2DStrategyImpl(*other.hHomMat2DStrategyImpl_);
}

HHomMat2DStrategy& HHomMat2DStrategy::operator=(const HHomMat2DStrategy& other)
{
	if (this != &other)
	{
		delete hHomMat2DStrategyImpl_;
		hHomMat2DStrategyImpl_ = new HHomMat2DStrategyImpl(*other.hHomMat2DStrategyImpl_);
	}
	return *this;
}

HHomMat2DStrategy::HHomMat2DStrategy(HHomMat2DStrategy&& other) noexcept
{
	hHomMat2DStrategyImpl_ = other.hHomMat2DStrategyImpl_;
	other.hHomMat2DStrategyImpl_ = nullptr;
}

HHomMat2DStrategy& HHomMat2DStrategy::operator=(HHomMat2DStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete hHomMat2DStrategyImpl_;
		hHomMat2DStrategyImpl_ = other.hHomMat2DStrategyImpl_;
		other.hHomMat2DStrategyImpl_ = nullptr;
	}
	return *this;
}

Result<HHomMat2DStrategy> HHomMat2DStrategy::HomMat2dTranslate(double tx, double ty) const
{
	auto hHomMat = VISALGORITHM_WRAP_TRY_CATCH(hHomMat2DStrategyImpl_->hHomMat2D_.HomMat2dTranslate(tx, ty));
	return hHomMat.transform([this](const HalconCpp::HHomMat2D& hHomMat)
		{
			this->hHomMat2DStrategyImpl_->hHomMat2D_ = hHomMat;
			return *this;
		});
}

VISALGORITHM_NAMESPACE_END