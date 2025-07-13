#pragma once

#include "BasicReturnInternal.h"
#include "Image.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HImage GetHImage(const Image& image);
Image FromHImage(const HalconCpp::HImage& hImage);
Result<Image> ResultFromHImage(const Result<HalconCpp::HImage>& result);

VISALGORITHM_NAMESPACE_END