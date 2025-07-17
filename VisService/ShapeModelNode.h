#pragma once
#include "BasicDefs.h"
#include "VisAlgorithm.h"

VISSERVICE_NAMESPACE_BEGIN

struct CreateShapeModelParams : public CGraph::GParam
{
	VisAlgorithm::CreateShapeModelParams createShapeModelPrams_;
};

class CreateShapeModelNode : public  CGraph::GNode
{
public:
	CStatus init() override
	{

		return CStatus();
	}

	CStatus run() override
	{
		return CStatus();
	}
};

class FindShapeModelNode : public  CGraph::GNode
{
public:
	CStatus init() override
	{
		return CStatus();
	}

	CStatus run() override
	{
		return CStatus();
	}

};

VISSERVICE_NAMESPACE_END