#pragma once

#include "BasicType.h"

VISALGORITHM_NAMESPACE_BEGIN

inline int Image::GetBytesPerPixel(PixelFormat format)
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

template<typename Derived>
void HImageMixin<Derived>::GenImageExtern()
{
	Derived* derived = static_cast<Derived*>(this);
	if (!derived->data_)
		return;

	switch (derived->pixelFormat_)
	{
	case PixelFormat::Mono8:
		hImage_.GenImage1Extern("byte", derived->width_, derived->height_, derived->data_.get(), nullptr);
		break;
	default:
		break;
	}
}

VISALGORITHM_NAMESPACE_END