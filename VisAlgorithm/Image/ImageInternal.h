#pragma once

#include "HalconCpp.h"
#include "Image.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HImage GetHImage(const Image& image);
Image FromHImage(const HalconCpp::HImage& hImage);

VISALGORITHM_NAMESPACE_END