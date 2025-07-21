#pragma once
#include "BasicDefs.h"
#include "VisAlgorithm.h"
#include "../../BaseNode.h"

VISSERVICE_NAMESPACE_BEGIN

struct ShapeMatchingParams
{
	std::string keyName_;
	VisAlgorithm::Image refImage_;
	VisAlgorithm::CreateShapeModelParams modelParams_;
	VisAlgorithm::ShapeModel shapeModel_;
	VisAlgorithm::FindShapeModelParams runParams_;
};


class ShapeMatching : public BaseNode
{
public:
	ShapeMatching(std::string name);

public:
	virtual CStatus init() override
	{
		//shapeMatchingParams_.readDb(taskName_);
		CGraph::CGRAPH_ECHO("ShapeMatchingNode::init()");
		return CStatus();
	}

	virtual CStatus run() override
	{
		CGraph::CGRAPH_ECHO("ShapeMatchingNode::run()");
		return CStatus();
	}

private:
	ShapeMatchingParams shapeMatchingParams_;
};

VISSERVICE_NAMESPACE_END