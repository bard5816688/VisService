// Represents a homogeneous 2D transformation matrix
#pragma once

#include "HHomMat2DStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsHomMat2DStrategy Strategy>
class HomMat2DContext
{
public:
	Result<Strategy> HomMat2dTranslate(double Tx, double Ty) const;

private:
	Strategy strategy_;
};

VISALGORITHM_NAMESPACE_END

#include "HomMat2D.inl"