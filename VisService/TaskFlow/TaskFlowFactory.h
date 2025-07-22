#pragma once

#include "../Basic/BasicReturn.h"
#include "CGraph.h"
#include "TaskFlowParams.h"

#define USE_PREDEFINED_PIPELINE

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowFactory
{
public:
	static Return<CGraph::GPipelinePtr> Create(TaskFlowTopologyType tyepe)
	{
#ifdef USE_PREDEFINED_PIPELINE
		auto pipeLine = CGraph::GPipelineFactory::create();
		ReturnVoid ret;
		switch (tyepe)
		{
		case VisService::TaskFlowTopologyType::DispensingMatching:
			ret = BuildDispensingMatching(pipeLine);
			break;
		case VisService::TaskFlowTopologyType::PostDispensingInspectionNormal:
			ret = BuildPostDispensingInspectionNormal(pipeLine);
			break;
		default:
			ret = VIS_RETURN_UNEXPECTE("TaskFlowFactory::Create()", "No suport", ErrorCode::Unknown);
			break;
		}
		if (!ret)
		{
			CGraph::GPipelineFactory::remove(pipeLine);
			return tl::unexpected(ret.error());
		}
		return pipeLine;
#elif
		//∂¡»°JSONππΩ®PipeLine
#endif
	}

	static ReturnVoid Remove(CGraph::GPipelinePtr pipeLine)
	{
		CGraph::GPipelineFactory::remove(pipeLine);
	}

#ifdef USE_PREDEFINED_PIPELINE
	static ReturnVoid BuildDispensingMatching(CGraph::GPipelinePtr pipeLine);
	static ReturnVoid BuildPostDispensingInspectionNormal(CGraph::GPipelinePtr pipeLine);

#elif
private:
	std::map<std::string, QJsonObject> taskFlowTopology_;

#endif

};

VISSERVICE_NAMESPACE_END