#pragma once

#include "../Basic/BasicReturnInternal.h"
#include "Contour.h"

VISALGORITHM_NAMESPACE_BEGIN

class ContourInternalUtils
{
public:
	static HalconCpp::HXLDCont GetHXldContour(const Contour& region);
	static Contour FromHXldContour(const HalconCpp::HXLDCont& hRegion);
	static Result<Contour> ResultFromHXldContour(const Result<HalconCpp::HXLDCont>& result);
};

VISALGORITHM_NAMESPACE_END