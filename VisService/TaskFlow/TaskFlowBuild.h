#pragma once
#include "../Component/CGraph/CGraph.h"
#include "TaskFlowParams.h"

#define USE_PREDEFINED_PIPELINE

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowBuild
{
public:
	static ReturnVoid Build(CGraph::GPipelinePtr pipeLine, TaskFlowTopologyType type, const std::string& taskName);

private:
#ifdef USE_PREDEFINED_PIPELINE
	static ReturnVoid BuildDispensingMatching(CGraph::GPipelinePtr pipeLine, const std::string& taskName);
	static ReturnVoid BuildPostDispensingInspectionNormal(CGraph::GPipelinePtr pipeLine, const std::string& taskName);

#elif
	static ReturnVoid BuildFromJson(CGraph::GPipelinePtr pipeLine, TaskFlowTopologyType type);
#endif

};

VISSERVICE_NAMESPACE_END