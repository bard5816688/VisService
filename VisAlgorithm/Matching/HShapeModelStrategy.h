#pragma once

#include "ShapeModelStrategyConcept.h"

VISALGORITHM_NAMESPACE_BEGIN

class HShapeModelStrategyImpl;

class VisAlgorithmApi HShapeModelStrategy
{
public:
	HShapeModelStrategy();
	~HShapeModelStrategy();

	ResultVoid ReadShapeModel(const char* fileName);
	ResultVoid CreateShapeModel(const CreateShapeModelParams& params);

private:
	HShapeModelStrategyImpl* hShapeModelStrategyImpl_;
};

VISALGORITHM_NAMESPACE_END