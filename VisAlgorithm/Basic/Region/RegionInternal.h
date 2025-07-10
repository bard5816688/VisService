#pragma once

#include "HalconCpp.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HRegion GetHRegion(const Region& region);
Region FromHRegion(const HalconCpp::HRegion& hRegion);

VISALGORITHM_NAMESPACE_END