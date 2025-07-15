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

template class ShapeModelContext<HShapeModelStrategy>;
using HShapeModel = ShapeModelContext<HShapeModelStrategy>;

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"
