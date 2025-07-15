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
	if (this != &other) {
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
	if (this != &other) {
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


VISALGORITHM_NAMESPACE_END