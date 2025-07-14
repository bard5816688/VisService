#pragma once

#include "BasicDefs.h"
#include "BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename T>
concept IsHomMat2DStrategy = requires(
    T t,
    double tx, double ty
	)
{
	{ t.HomMat2dTranslate(tx, ty) }	->std::same_as<Result<T>>;
};


VISALGORITHM_NAMESPACE_END