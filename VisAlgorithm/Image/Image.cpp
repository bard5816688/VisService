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

Image::Image(const char* type, int64_t width, int64_t height)
	: imageImpl_(new ImageImpl)
{
	imageImpl_->hImage_.GenImageConst(type, width, height);
}

Image::Image(const char* type, int64_t width, int64_t height, void* pixelPointer)
	: imageImpl_(new ImageImpl)
{
	imageImpl_->hImage_.GenImage1(type, width, height, pixelPointer);
}

Image::Image(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc)
	: imageImpl_(new ImageImpl)
{
	imageImpl_->hImage_.GenImage1Extern(type, width, height, pixelPointer, clearProc);
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

Result<Tuple> Image::Width()
{
	return ResultFromHTuple(WRAP_HALCON_TRY(imageImpl_->hImage_.Width()));
}

Result<Tuple> Image::Height()
{
	return ResultFromHTuple(WRAP_HALCON_TRY(imageImpl_->hImage_.Height()));
}

Result<Tuple> Image::CountChannels() const
{
	return ResultFromHTuple(WRAP_HALCON_TRY(imageImpl_->hImage_.CountChannels()));
}

ImageImpl* Image::ImplPtr() const
{
	return imageImpl_;
}


HalconCpp::HImage GetHImage(const Image& image)
{
	return image.ImplPtr()->hImage_;
}

Image FromHImage(const HalconCpp::HImage& hImage)
{
	Image img;
	img.ImplPtr()->hImage_ = hImage;
	return img;
}

Result<Image> ResultFromHImage(const Result<HalconCpp::HImage>& result)
{
	return result.transform(FromHImage);
}

VISALGORITHM_NAMESPACE_END