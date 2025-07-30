#include "TaskFlowBuild.h"
#include "./Module/Matching/ShapeMatching.h"
#include "./Module/Matching/ShapeMatchingUi.h"

VISSERVICE_NAMESPACE_BEGIN

ReturnVoid TaskFlowBuild::Build(CGraph::GPipelinePtr pipeLine, TaskFlowTopologyType type, const std::string& taskName)
{
#ifdef USE_PREDEFINED_PIPELINE
		pipeLine = CGraph::GPipelineFactory::create();
		ReturnVoid ret;
		switch (type)
		{
		case VisService::TaskFlowTopologyType::DispensingMatching:
			ret = BuildDispensingMatching(pipeLine, taskName);
			break;
		case VisService::TaskFlowTopologyType::PostDispensingInspectionNormal:
			ret = BuildPostDispensingInspectionNormal(pipeLine, taskName);
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

#endif
	return ret;
}

ReturnVoid TaskFlowBuild::BuildDispensingMatching(CGraph::GPipelinePtr pipeLine, const std::string& taskName)
{
	auto ShapeMatching = ModuleRegistry::Instance().CreateLogic("ShapeMatching", taskName);
	auto ShapeMatchingUi = ModuleRegistry::Instance().CreateUi("ShapeMatching", taskName, nullptr);
	CGraph::GElementPPtr tste;
	auto status = pipeLine->registerGNode(tste);
	return ReturnVoid();
}

ReturnVoid TaskFlowBuild::BuildPostDispensingInspectionNormal(CGraph::GPipelinePtr pipeLine, const std::string& taskName)
{
	return ReturnVoid();
}

VISSERVICE_NAMESPACE_END