#include "ImageInternal.h"
#include "TupleInternal.h"
#include "RegionInternal.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HImageStrategy::Impl
{
public:
	HalconCpp::HImage& GetHobj()
	{
		return hImage_;
	}

	HalconCpp::HImage hImage_;
};

HImageStrategy::HImageStrategy()
	: impl_(new Impl)
{
}

HImageStrategy::~HImageStrategy()
{
	delete impl_;
}

HImageStrategy::HImageStrategy(const HImageStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HImageStrategy& HImageStrategy::operator=(const HImageStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HImageStrategy::HImageStrategy(HImageStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HImageStrategy& HImageStrategy::operator=(HImageStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

ResultVoid HImageStrategy::GenImageConst(const char* type, int64_t width, int64_t height)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hImage_.GenImageConst(type, width, height));
	return res;
}

ResultVoid HImageStrategy::GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hImage_.GenImage1(type, width, height, pixelPointer));
	return res;
}

ResultVoid HImageStrategy::GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hImage_.GenImage1Extern(type, width, height, pixelPointer, clearProc));
	return res;
}

ResultVoid HImageStrategy::GetImageSize(int64_t* width, int64_t* height) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hImage_.GetImageSize(width, height));
	return res;
}

Result<Tuple> HImageStrategy::CountChannels() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, impl_->hImage_.CountChannels());
	return TupleInternalUtils::ResultFromHTuple(res);
}

HImageStrategy::Impl* HImageStrategy::GetImpl() const
{
	return impl_;
}

HalconCpp::HImage ImageInternalUtils::GetHImage(const Image& image)
{
	return image.GetImpl()->GetHobj();
}

Image ImageInternalUtils::FromHImage(const HalconCpp::HImage& hImage)
{
	Image img;
	img.GetImpl()->GetHobj() = hImage;
	return img;
}

Result<Image> ImageInternalUtils::ResultFromHImage(const Result<HalconCpp::HImage>& result)
{
	return result.transform(FromHImage);
}

VISALGORITHM_NAMESPACE_END