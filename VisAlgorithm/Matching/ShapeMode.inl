#pragma once

#include "ShapeModel.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>::ShapeModelContext()
{

}

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>::~ShapeModelContext()
{

}

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>::ShapeModelContext(const ShapeModelContext& other)
	: strategy_(other.strategy_)
{

}

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>& ShapeModelContext<Strategy>::operator=(const ShapeModelContext<Strategy>& other)
{
	if (this != &other)
	{
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>::ShapeModelContext(ShapeModelContext<Strategy>&& other) noexcept
	: strategy_(std::move(other.strategy_))
{

}

template<IsShapeModelStrategy Strategy>
ShapeModelContext<Strategy>& ShapeModelContext<Strategy>::operator=(ShapeModelContext<Strategy>&& other) noexcept
{
	if (this != &other)
	{
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::ReadShapeModel(const char* fileName)
{
	return strategy_.ReadShapeModel(fileName);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::CreateShapeModel(const CreateShapeModelParams& params)
{
	return strategy_.CreateShapeModel(params);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::FindShapeModel(const FindShapeModelParams& params) const
{
	return strategy_.FindShapeModel(params);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::ClearShapeModel()
{
	return strategy_.ClearShapeModel();
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::GetShapeModelParams(const ShapeModelParams& params) const
{
	return strategy_.GetShapeModelParams();
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::SetShapeModelParam(const std::string& paramName, double paramValue)
{
	return strategy_.SetShapeModelParam(paramName, paramValue);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::WriteShapeModel(const char* FileName) const
{
	return strategy_.WriteShapeModel(FileName);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::GetShapeModelOrigin(double* row, double* column) const
{
	return strategy_.GetShapeModelOrigin(row, column);
}

template<IsShapeModelStrategy Strategy>
ResultVoid ShapeModelContext<Strategy>::SetShapeModelOrigin(int row, int column)
{
	return strategy_.SetShapeModelOrigin(row, column);
}


VISALGORITHM_NAMESPACE_END