#pragma once

#include "BasicReturnInternal.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HRegion GetHRegion(const Region& region);
Region FromHRegion(const HalconCpp::HRegion& hRegion);
Result<Region> ResultFromHRegion(const Result<HalconCpp::HRegion>& result);

VISALGORITHM_NAMESPACE_END