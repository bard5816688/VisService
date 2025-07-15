#pragma once

#include "ShapeModelStrategyConcept.h"

VISALGORITHM_NAMESPACE_BEGIN

class HShapeModelStrategyImpl;

class VisAlgorithmApi HShapeModelStrategy
{
	class Impl;
public:
	HShapeModelStrategy();
	~HShapeModelStrategy();
	HShapeModelStrategy(const HShapeModelStrategy& other);
	HShapeModelStrategy& operator=(const HShapeModelStrategy& other);
	HShapeModelStrategy(HShapeModelStrategy&& other) noexcept;
	HShapeModelStrategy& operator=(HShapeModelStrategy&& other) noexcept;

	ResultVoid ReadShapeModel(const char* fileName);
	ResultVoid CreateShapeModel(const CreateShapeModelParams& params);

private:
	Impl* impl_;
};

VISALGORITHM_NAMESPACE_END