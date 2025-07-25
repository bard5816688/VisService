#include "HShapeModelStrategy.h"
#include "HalconCpp.h"
#include "../Image/ImageInternal.h"
#include "../Tuple/TupleInternal.h"
#include "../Region/RegionInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HShapeModelStrategy::Impl
{
public:
	HalconCpp::HShapeModel hShapeModel_;
};

HShapeModelStrategy::HShapeModelStrategy()
	: impl_(new Impl)
{

}

HShapeModelStrategy::~HShapeModelStrategy()
{
	delete impl_;
}

HShapeModelStrategy::HShapeModelStrategy(const HShapeModelStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HShapeModelStrategy& HShapeModelStrategy::operator=(const HShapeModelStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HShapeModelStrategy::HShapeModelStrategy(HShapeModelStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HShapeModelStrategy& HShapeModelStrategy::operator=(HShapeModelStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

ResultVoid HShapeModelStrategy::ReadShapeModel(const char* fileName)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.ReadShapeModel(fileName));
	return res;
}

ResultVoid HShapeModelStrategy::CreateShapeModel(const CreateShapeModelParams& params)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.CreateShapeModel(ImageInternalUtils::GetHImage(params.templateImg_), params.numLevels_, params.angleStep_,
		params.angleExtent_, params.angleStep_, params.optimization_.c_str(), params.metric_.c_str(), params.contrast_, params.minContrast_));
	return res;
}

ResultVoid HShapeModelStrategy::FindShapeModel(const FindShapeModelParams& params) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.FindShapeModel(ImageInternalUtils::GetHImage(params.searchImage), params.angleStart,
		params.angleExtent, params.minScore, params.numMatches, params.maxOverlap, params.subPixel.c_str(), params.numLevels, params.greediness,
		TupleInternalUtils::GetHTuplePtr(params.row), TupleInternalUtils::GetHTuplePtr(params.column), TupleInternalUtils::GetHTuplePtr(params.angle), TupleInternalUtils::GetHTuplePtr(params.score)));
	return res;
}

ResultVoid HShapeModelStrategy::ClearShapeModel()
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.ClearShapeModel());
	return res;
}

Result<int64_t> HShapeModelStrategy::GetShapeModelParams(const ShapeModelParams& params) const
{
	HalconCpp::HString metric;
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.GetShapeModelParams(params.angleStart, params.angleExtent, params.angleStep, params.scaleMin, params.scaleMax, params.scaleStep, &metric, params.minContrast));
	*params.metric = metric.Text();
	return res;
}

ResultVoid HShapeModelStrategy::SetShapeModelOrigin(int row, int column)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.SetShapeModelOrigin(row, column));
	return res;
}

ResultVoid HShapeModelStrategy::GetShapeModelOrigin(double* row, double* column) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.GetShapeModelOrigin(row, column));
	return res;
}

ResultVoid HShapeModelStrategy::SetShapeModelParam(const std::string& paramName, double paramValue)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.SetShapeModelParam(HalconCpp::HTuple(paramName.c_str()), HalconCpp::HTuple(paramValue)));
	return res;
}

ResultVoid HShapeModelStrategy::WriteShapeModel(const std::string& fileName) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.WriteShapeModel(fileName.c_str()));
	return res;
}

VISALGORITHM_NAMESPACE_END