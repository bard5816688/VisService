#include "HShapeModelStrategy.h"
#include "HalconCpp.h"
#include "ImageInternal.h"
#include "TupleInternal.h"
#include "RegionInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HShapeModelStrategyImpl
{
public:
	HalconCpp::HShapeModel hShapeModel_;
};

HShapeModelStrategy::HShapeModelStrategy()
	: hShapeModelStrategyImpl_(new HShapeModelStrategyImpl)
{

}

HShapeModelStrategy::~HShapeModelStrategy()
{
	delete hShapeModelStrategyImpl_;
}

HShapeModelStrategy::HShapeModelStrategy(const HShapeModelStrategy& other)
{
	hShapeModelStrategyImpl_ = new HShapeModelStrategyImpl(*other.hShapeModelStrategyImpl_);
}

HShapeModelStrategy& HShapeModelStrategy::operator=(const HShapeModelStrategy& other)
{
	if (this != &other)
	{
		delete hShapeModelStrategyImpl_;
		hShapeModelStrategyImpl_ = new HShapeModelStrategyImpl(*other.hShapeModelStrategyImpl_);
	}
	return *this;
}

HShapeModelStrategy::HShapeModelStrategy(HShapeModelStrategy&& other) noexcept
{
	hShapeModelStrategyImpl_ = other.hShapeModelStrategyImpl_;
	other.hShapeModelStrategyImpl_ = nullptr;
}

HShapeModelStrategy& HShapeModelStrategy::operator=(HShapeModelStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete hShapeModelStrategyImpl_;
		hShapeModelStrategyImpl_ = other.hShapeModelStrategyImpl_;
		other.hShapeModelStrategyImpl_ = nullptr;
	}
	return *this;
}

ResultVoid HShapeModelStrategy::ReadShapeModel(const char* fileName)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, hShapeModelStrategyImpl_->hShapeModel_.ReadShapeModel(fileName));
	return res;
}

ResultVoid HShapeModelStrategy::CreateShapeModel(const CreateShapeModelParams& params)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, hShapeModelStrategyImpl_->hShapeModel_.CreateShapeModel(ImageInternal::GetHImage(params.templateImg_), params.numLevels_, params.angleStep_, params.angleExtent_, params.angleStep_, params.optimization_, params.metric_, params.contrast_, params.minContrast_));
	return res;
}

VISALGORITHM_NAMESPACE_END