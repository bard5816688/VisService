#pragma once
#include "HomMat2D.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsHomMat2DStrategy Strategy>
Result<Strategy> HomMat2D<Strategy>::HomMat2dTranslate(double tx, double ty) const
{
	return strategy_.HomMat2dTranslate(tx, ty);
}

VISALGORITHM_NAMESPACE_END