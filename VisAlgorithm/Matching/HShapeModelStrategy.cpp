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
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hShapeModel_.CreateShapeModel(ImageInternalUtils::GetHImage(params.templateImg_), params.numLevels_, params.angleStep_, params.angleExtent_, params.angleStep_, params.optimization_, params.metric_, params.contrast_, params.minContrast_));
	return res;
}

VISALGORITHM_NAMESPACE_END