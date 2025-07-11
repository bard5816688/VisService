#pragma once

#include "VisAlgorithmDefs.h"
#include "HShapeModelStrategy.h"
#include "VisShapeModelStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN


template<IsShapeModelStrategy Strategy>
class ShapeModel 
{
public:
	void ReadShapeModel(const char* fileName);
	void CreateShapeModel(const CreateShapeModelParams& params);

private:
    Strategy strategy_;
};

template class ShapeModel<HShapeModelStrategy>;
//template class ShapeModel<VisShapeModelStrategy>;

using HShapeModel = ShapeModel<HShapeModelStrategy>;
//using VisShapeModel = ShapeModel<VisShapeModelStrategy>;

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"
