#include "ImageInternal.h"
#include "TupleInternal.h"
#include "RegionInternal.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageImpl
{
public:
	HalconCpp::HImage hImage_;
};

Image::Image()
	: imageImpl_(new ImageImpl)
{
}

Image::~Image()
{
	delete imageImpl_;
}

Image::Image(const Image& other)
{
	imageImpl_ = new ImageImpl(*other.imageImpl_);
}

Image& Image::operator=(const Image& other)
{
	if (this != &other)
	{
		delete imageImpl_;
		imageImpl_ = new ImageImpl(*other.imageImpl_);
	}
	return *this;
}

Image::Image(Image&& other) noexcept
{
	imageImpl_ = other.imageImpl_;
	other.imageImpl_ = nullptr;
}

Image& Image::operator=(Image&& other) noexcept
{
	if (this != &other)
	{
		delete imageImpl_;
		imageImpl_ = other.imageImpl_;
		other.imageImpl_ = nullptr;
	}
	return *this;
}

ResultVoid Image::GenImageConst(const char* type, int64_t width, int64_t height)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.GenImageConst(type, width, height));
	return res;
}

ResultVoid Image::GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.GenImage1(type, width, height, pixelPointer));
	return res;
}

ResultVoid Image::GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc)
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.GenImage1Extern(type, width, height, pixelPointer, clearProc));
	return res;
}

Result<Tuple> Image::Width()
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.Width());
	return TupleInternal::ResultFromHTuple(res);
}

Result<Tuple> Image::Height()
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.Height());
	return TupleInternal::ResultFromHTuple(res);
}

Result<Tuple> Image::CountChannels() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(res, imageImpl_->hImage_.CountChannels());
	return TupleInternal::ResultFromHTuple(res);
}

HalconCpp::HImage ImageInternal::GetHImage(const Image& image)
{
	return image.imageImpl_->hImage_;
}

Image ImageInternal::FromHImage(const HalconCpp::HImage& hImage)
{
	Image img;
	img.imageImpl_->hImage_ = hImage;
	return img;
}

Result<Image> ImageInternal::ResultFromHImage(const Result<HalconCpp::HImage>& result)
{
	return result.transform(FromHImage);
}

VISALGORITHM_NAMESPACE_END