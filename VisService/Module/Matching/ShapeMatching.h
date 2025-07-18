#pragma once
#include "BasicDefs.h"
#include "VisAlgorithm.h"
#include <QWidget>

VISSERVICE_NAMESPACE_BEGIN


struct ShapeModelParams
{
	VisAlgorithm::Image refImage_;
	VisAlgorithm::ShapeModel shapeModel_;
};

struct ShapeMatchingRunParams
{

};


struct ShapeMatchingParams
{
	ModuleBasicParams basicParams_;
	ShapeMatchingRunParams runParams_;
	ShapeModelParams modelParams_;
};

VISSERVICE_NAMESPACE_END