#include "TaskFlow.h"
#include "TaskFlowBuilder.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlow::TaskFlow()
{
}

TaskFlow::~TaskFlow()
{
}

ReturnVoid TaskFlow::Initialize(const TaskFlowInitParams& params)
{
	params_ = params;
	VIS_RETURN_IF_UNEXPECTED(pipelineType, GetPipeLineName(params_.topologyType_));
	VIS_RETURN_IF_UNEXPECTED(pipeline, GlobalTaskFlowBuilder().GetPipeLine(*pipelineType));

	//pipeLine_->createGParam<TaskFlowInitGParams>("TaskFlowInitGParams");
	//auto taskFlowGParams = pipeLine_->getGParam<TaskFlowInitGParams>("TaskFlowInitGParams");
	//taskFlowGParams->taskName_ = params.taskName_;
	//taskFlowGParams->deputyTaskName_ = params.deputyTaskName_;
	//taskFlowGParams->station_ = params.station_;
	(*pipeline)->init();
	return ReturnVoid();
}

ReturnVoid TaskFlow::Run(const TaskFlowRunParams& params)
{
	VIS_RETURN_IF_UNEXPECTED(pipelineType, GetPipeLineName(params_.topologyType_));
	VIS_RETURN_IF_UNEXPECTED(pipeline, GlobalTaskFlowBuilder().GetPipeLine(*pipelineType));
	(*pipeline)->run();
	return ReturnVoid();
}

ReturnVoid TaskFlow::AsyncRun(const TaskFlowRunParams& params)
{
	VIS_RETURN_IF_UNEXPECTED(pipelineType, GetPipeLineName(params_.topologyType_));
	VIS_RETURN_IF_UNEXPECTED(pipeline, GlobalTaskFlowBuilder().GetPipeLine(*pipelineType));
	(*pipeline)->asyncRun();
	return ReturnVoid();
}

Return<QJsonObject> TaskFlow::GetResult()
{
	VIS_RETURN_IF_UNEXPECTED(pipelineType, GetPipeLineName(params_.topologyType_));
	VIS_RETURN_IF_UNEXPECTED(pipeline, GlobalTaskFlowBuilder().GetPipeLine(*pipelineType));
	return (*pipeline)->GetResult();
}

Return<VisAlgorithm::Image> TaskFlow::GetSourceImage()
{
	return Return<VisAlgorithm::Image>();
}

Return<VisAlgorithm::Image> TaskFlow::GetResultImage()
{
	return Return<VisAlgorithm::Image>();
}

Return<std::string> TaskFlow::GetPipeLineName(TaskFlowTopologyType type)
{
	std::string pipelineType = "";
	switch (type)
	{
	case VisService::TaskFlowTopologyType::DispensingMatching:
		pipelineType = "DispensingMatching";
		break;
	case VisService::TaskFlowTopologyType::PostDispensingInspectionNormal:
		pipelineType = "PostDispensingInspectionNormal";
		break;
	default:
		return VIS_RETURN_UNEXPECTED(ModuleErrorCode::TaskFlow, ErrorCode::SystemError, "Cannot support task flow type", "TaskFlow::GetTaskName()");
		break;
	}
	return pipelineType;
}


VISSERVICE_NAMESPACE_END