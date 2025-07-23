#include "TaskFlowBuild.h"
#include "./Module/Matching/ShapeMatching.h"

VISSERVICE_NAMESPACE_BEGIN

ReturnVoid TaskFlowBuild::Build(CGraph::GPipelinePtr pipeLine, TaskFlowTopologyType type)
{
#ifdef USE_PREDEFINED_PIPELINE
		auto pipeLine = CGraph::GPipelineFactory::create();
		ReturnVoid ret;
		switch (type)
		{
		case VisService::TaskFlowTopologyType::DispensingMatching:
			ret = BuildDispensingMatching(pipeLine);
			break;
		case VisService::TaskFlowTopologyType::PostDispensingInspectionNormal:
			ret = BuildPostDispensingInspectionNormal(pipeLine);
			break;
		default:
			ret = VIS_RETURN_UNEXPECTED(ModuleErrorCode::TaskFlow, ErrorCode::SystemError, "", "TaskFlowBuild::Build()");
			break;
		}
		if (!ret)
		{
			CGraph::GPipelineFactory::remove(pipeLine);
			return tl::unexpected(ret.error());
		}
#elif
	//∂¡»°JSONππΩ®PipeLine
#endif
}

ReturnVoid TaskFlowBuild::BuildDispensingMatching(CGraph::GPipelinePtr pipeLine)
{
	return ReturnVoid();
}

ReturnVoid TaskFlowBuild::BuildPostDispensingInspectionNormal(CGraph::GPipelinePtr pipeLine)
{
	return ReturnVoid();
}

VISSERVICE_NAMESPACE_END