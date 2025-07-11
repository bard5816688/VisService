#pragma once

#include "ShapeModelStrategyConcept.h"

VISALGORITHM_NAMESPACE_BEGIN

class HShapeModelStrategyImpl;

class VisAlgorithmApi HShapeModelStrategy
{
public:
	HShapeModelStrategy();
	~HShapeModelStrategy();
	void ReadShapeModel(const char* fileName);
	void CreateShapeModel(const CreateShapeModelParams& params);


private:
	HShapeModelStrategyImpl* hShapeModelStrategyImpl_;
};

VISALGORITHM_NAMESPACE_END