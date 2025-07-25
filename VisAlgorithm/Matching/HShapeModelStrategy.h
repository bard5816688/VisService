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
	ResultVoid FindShapeModel(const FindShapeModelParams& params) const;
	ResultVoid ClearShapeModel();
	Result<int64_t> GetShapeModelParams(const ShapeModelParams& params) const;
	ResultVoid SetShapeModelOrigin(int row, int column);
	ResultVoid GetShapeModelOrigin(double* row, double* column) const;
	ResultVoid SetShapeModelParam(const std::string& paramName, double paramValue);
	ResultVoid WriteShapeModel(const std::string& fileName) const;
private:
	Impl* impl_;
};

VISALGORITHM_NAMESPACE_END