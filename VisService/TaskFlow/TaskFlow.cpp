#include "TaskFlow.h"
#include "TaskFlowBuild.h"
#include "TaskFlowContextParams.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlow::TaskFlow()
	: pipeLine_(nullptr)
{

}

TaskFlow::~TaskFlow()
{
	if (pipeLine_)
	{
		pipeLine_->destroy();
		CGraph::GPipelineFactory::remove(pipeLine_);
	}
}

ReturnVoid TaskFlow::Initialize(const TaskFlowInitParams& params)
{
	if (pipeLine_)
	{
		pipeLine_->destroy();
		CGraph::GPipelineFactory::remove(pipeLine_);
	}
	pipeLine_ = CGraph::GPipelineFactory::create();
	VIS_RETURN_IF_UNEXPECTED(TaskFlowBuild::Build(pipeLine_, params.topologyType_));
	//注入全局参数
	pipeLine_->createGParam<TaskFlowInitGParams>("TaskFlowInitGParams");
	auto taskFlowGParams = pipeLine_->getGParam<TaskFlowInitGParams>("TaskFlowInitGParams");
	taskFlowGParams->taskName_ = params.taskName_;
	taskFlowGParams->deputyTaskName_ = params.deputyTaskName_;
	taskFlowGParams->station_ = params.station_;
	pipeLine_->init();
	return ReturnVoid();
}

ReturnVoid TaskFlow::Run(const TaskFlowRunParams& params)
{
	VIS_RETURN_IF_NULLPTR_WITH_MSG(pipeLine_, ModuleErrorCode::TaskFlow, "TaskFlow::pipeLine_ is nullptr!");
	pipeLine_->run();
	return ReturnVoid();
}

ReturnVoid TaskFlow::AsyncRun(const TaskFlowRunParams& params)
{
	VIS_RETURN_IF_NULLPTR_WITH_MSG(pipeLine_, ModuleErrorCode::TaskFlow, "TaskFlow::pipeLine_ is nullptr!");
	pipeLine_->asyncRun();
	return ReturnVoid();
}

Return<QJsonObject> TaskFlow::GetResult()
{

}

Return<VisAlgorithm::Image> TaskFlow::GetSourceImage()
{

}

Return<VisAlgorithm::Image> TaskFlow::GetResultImage()
{

}

VISSERVICE_NAMESPACE_END