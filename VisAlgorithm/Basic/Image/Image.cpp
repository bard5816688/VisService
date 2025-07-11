#include "ImageInternal.h"
#include "TupleInternal.h"
#include "RegionInternal.h"

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

Tuple Image::Width()
{
	return FromHTuple(imageImpl_->hImage_.Width());
}

Tuple Image::Height()
{
	return FromHTuple(imageImpl_->hImage_.Height());
}

Tuple Image::CountChannels() const
{
	return FromHTuple(imageImpl_->hImage_.CountChannels());
	return Tuple();
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

VISALGORITHM_NAMESPACE_END