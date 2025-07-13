#pragma once

#include "HShapeModelStrategy.h"
#include "VisShapeModelStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN


template<IsShapeModelStrategy Strategy>
class ShapeModel 
{
public:
	ResultVoid ReadShapeModel(const char* fileName);
	ResultVoid CreateShapeModel(const CreateShapeModelParams& params);

private:
    Strategy strategy_;
};

template class ShapeModel<HShapeModelStrategy>;
//template class ShapeModel<VisShapeModelStrategy>;

using HShapeModel = ShapeModel<HShapeModelStrategy>;
//using VisShapeModel = ShapeModel<VisShapeModelStrategy>;

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"
