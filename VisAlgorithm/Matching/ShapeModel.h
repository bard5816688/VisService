#pragma once
#include "HShapeModelStrategy.h"
#include "VisShapeModelStrategy.h"
#include "../Contour/Contour.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsShapeModelStrategy Strategy>
class ShapeModelContext
{
public:
	ShapeModelContext();
	~ShapeModelContext();
	ShapeModelContext(const ShapeModelContext& other);
	ShapeModelContext& operator=(const ShapeModelContext& other);
	ShapeModelContext(ShapeModelContext&& other) noexcept;
	ShapeModelContext& operator=(ShapeModelContext&& other) noexcept;

	ResultVoid ReadShapeModel(const char* fileName);
	ResultVoid CreateShapeModel(const CreateShapeModelParams& params);
	ResultVoid FindShapeModel(const FindShapeModelParams& params) const;
	ResultVoid ClearShapeModel();
	ResultVoid GetShapeModelParams(const ShapeModelParams& params) const;
	ResultVoid SetShapeModelOrigin(int row, int column);
	ResultVoid GetShapeModelOrigin(double* row, double* column) const;
	ResultVoid SetShapeModelParam(const std::string& paramName, double paramValue);
	ResultVoid WriteShapeModel(const char* fileName) const;
private:
	Strategy strategy_;
};

template class ShapeModelContext<HShapeModelStrategy>;
using ShapeModel = ShapeModelContext<HShapeModelStrategy>;

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"