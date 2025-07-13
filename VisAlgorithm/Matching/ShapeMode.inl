#pragma once

#include "ShapeModel.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModel<Strategy>::ReadShapeModel(const char* fileName)
{
	return strategy_.ReadShapeModel(fileName);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModel<Strategy>::CreateShapeModel(const CreateShapeModelParams& params)
{
	return strategy_.CreateShapeModel(params);
}


VISALGORITHM_NAMESPACE_END