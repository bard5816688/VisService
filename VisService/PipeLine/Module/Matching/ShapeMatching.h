#pragma once
#include "BasicDefs.h"
#include "VisAlgorithm.h"
#include "CGraph.h"

VISSERVICE_NAMESPACE_BEGIN

struct ShapeModelParams
{
	VisAlgorithm::Image refImage_;
	VisAlgorithm::CreateShapeModelParams modelParams_;
	VisAlgorithm::ShapeModel shapeModel_;
};

struct ShapeMatchingRunParams
{

};

struct ShapeMatchingParams : public CGraph::GParam
{
	//ModuleBasicParams basicParams_;
	ShapeMatchingRunParams runParams_;
	ShapeModelParams modelParams_;
};


class ShapeMatchingNode : public CGraph::GNode
{
public:
	virtual CStatus init() override
	{

		CGraph::CGRAPH_ECHO("ShapeMatchingNode::init()");
		return CStatus();
	}

	virtual CStatus run() override
	{
		CGraph::CGRAPH_ECHO("ShapeMatchingNode::run()");
		return CStatus();
	}

};

VISSERVICE_NAMESPACE_END