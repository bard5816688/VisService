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

ResultVoid HShapeModelStrategy::ReadShapeModel(const char* fileName)
{
	return WRAP_HALCON_TRY(hShapeModelStrategyImpl_->hShapeModel_.ReadShapeModel(fileName));
}

ResultVoid HShapeModelStrategy::CreateShapeModel(const CreateShapeModelParams& params)
{
	return WRAP_HALCON_TRY(hShapeModelStrategyImpl_->hShapeModel_.CreateShapeModel(GetHImage(params.templateImg_), params.numLevels_, params.angleStep_, params.angleExtent_, params.angleStep_, params.optimization_, params.metric_, params.contrast_, params.minContrast_));
}

VISALGORITHM_NAMESPACE_END