#include "VisImage.h"

VISALGORITHM_NAMESPACE_BEGIN

VisImage::VisImage()
	: width_(0)
	, height_(0)
	, pixelFormat_(PixelFormat::Unknown)
	, dataSize_(0)
	, frameId_(0)
{
}

VisImage::VisImage(uint32_t width, uint32_t height, PixelFormat format)
	: width_(width)
	, height_(height)
	, pixelFormat_(format)
	, frameId_(0)
{
	dataSize_ = width * height * GetBytesPerPixel(format);
	data_ = std::make_shared<uint8_t>();
}

VisImage::~VisImage()
{
}

int VisImage::GetBytesPerPixel(PixelFormat format)
{
	switch (format)
	{
	case PixelFormat::Mono8:
	case PixelFormat::BayerRg8:
	case PixelFormat::BayerGb8:
	case PixelFormat::BayerGr8:
	case PixelFormat::BayerBg8:
		return 1;
	case PixelFormat::Mono16:
	case PixelFormat::Mono10:
	case PixelFormat::Mono12:
		return 2;
	case PixelFormat::Rgb8:
	case PixelFormat::Bgr8:
		return 3;
	case PixelFormat::Rgba8:
	case PixelFormat::Bgra8:
		return 4;
	default:
		return 0;
	}
}

VISALGORITHM_NAMESPACE_END