#pragma once

#include "../Basic/BasicReturnInternal.h"
#include "Image.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageInternalUtils
{
public:
	static HalconCpp::HImage GetHImage(const Image& image);
	static Image FromHImage(const HalconCpp::HImage& hImage);
	static Result<Image> ResultFromHImage(const Result<HalconCpp::HImage>& result);
};

VISALGORITHM_NAMESPACE_END