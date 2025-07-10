#include "BasicType.h"

VISALGORITHM_NAMESPACE_BEGIN
Image::Image()
	: width_(0)
	, height_(0)
	, pixelFormat_(PixelFormat::Unknown)
	, dataSize_(0)
	, frameId_(0)
	, HImageMixin<Image>()
{
}

Image::Image(uint32_t width, uint32_t height, PixelFormat format)
	: width_(width)
	, height_(height)
	, pixelFormat_(format)
	, frameId_(0)
	, HImageMixin<Image>()
{
	dataSize_ = width * height * GetBytesPerPixel(format);
	data_ = std::make_shared<uint8_t>();
	HImageMixin<Image>::GenImageExtern();
}

HalconCpp::HImage& Image::GetHImage()
{
	return hImage_;
}

const HalconCpp::HImage& Image::GetHImage() const
{
	return hImage_;
}

uint32_t Image::Width()
{
	return width_;
}

uint32_t Image::Height()
{
	return height_;
}

std::shared_ptr<uint8_t> Image::Data()
{
	return data_;
}

PixelFormat Image::Format()
{
	return pixelFormat_;
}

VISALGORITHM_NAMESPACE_END