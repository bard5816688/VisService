#pragma once

#include "BasicReturnInternal.h"
#include "Image.h"

VISALGORITHM_NAMESPACE_BEGIN
class ImageInternal
{
public:
	static HalconCpp::HImage GetHImage(const Image& image);
	static Image FromHImage(const HalconCpp::HImage& hImage);
	static Result<Image> ResultFromHImage(const Result<HalconCpp::HImage>& result);

};

VISALGORITHM_NAMESPACE_END