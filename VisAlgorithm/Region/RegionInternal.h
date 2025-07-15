#pragma once

#include "BasicReturnInternal.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsRegionStrategy RegionStrategy>
class RegionInternalUtils
{
public:
	static HalconCpp::HRegion GetHRegion(const RegionStrategy& region);
	static RegionStrategy FromHRegion(const HalconCpp::HRegion& hRegion);
	static Result<RegionStrategy> ResultFromHRegion(const Result<HalconCpp::HRegion>& result);
};

extern template class RegionInternalUtils<HRegionStrategy>;

VISALGORITHM_NAMESPACE_END