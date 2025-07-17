#pragma once

#include "../Basic/BasicReturnInternal.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionInternalUtils
{
public:
	static HalconCpp::HRegion GetHRegion(const Region& region);
	static Region FromHRegion(const HalconCpp::HRegion& hRegion);
	static Result<Region> ResultFromHRegion(const Result<HalconCpp::HRegion>& result);
};

VISALGORITHM_NAMESPACE_END