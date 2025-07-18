#pragma once

#include "HShapeModelStrategy.h"
#include "VisShapeModelStrategy.h"

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

private:
    Strategy strategy_;
};
#ifdef USE_HALCON
#define DEFAULT_SHAPEMODEL_STRATEGY HShapeModelStrategy
#elif
#define DEFAULT_SHAPEMODEL_STRATEGY "NoSupported"
#endif
using ShapeModel = ShapeModelContext<DEFAULT_SHAPEMODEL_STRATEGY>;

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"
