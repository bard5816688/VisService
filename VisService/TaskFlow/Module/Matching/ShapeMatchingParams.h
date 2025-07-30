#pragma once
#include "../ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

struct ShapeMatchingParams
{
	std::string taskName_;
	ModuleInputParamPath<VisAlgorithm::Image> sourceImage_;
	ModuleInputParamPath<VisAlgorithm::Region> roi_;
	VisAlgorithm::Image refImage_;
	VisAlgorithm::CreateShapeModelParams modelParams_;
	VisAlgorithm::ShapeModel shapeModel_;
	VisAlgorithm::FindShapeModelParams runParams_;
};

ParamManager<ShapeMatchingParams>& GlobalShapeMatchingParams();

VISSERVICE_NAMESPACE_END