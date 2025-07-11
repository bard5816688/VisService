#pragma once

#include "ShapeModel.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsShapeModelStrategy Strategy>
void ShapeModel<Strategy>::ReadShapeModel(const char* fileName)
{
	strategy_.ReadShapeModel(fileName);
}

template<IsShapeModelStrategy Strategy>
void ShapeModel<Strategy>::CreateShapeModel(const CreateShapeModelParams& params)
{
	strategy_.CreateShapeModel(params);
}


VISALGORITHM_NAMESPACE_END