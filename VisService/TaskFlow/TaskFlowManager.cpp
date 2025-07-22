#include "TaskFlowManager.h"
#include "TaskFlowFactory.h"

VISSERVICE_NAMESPACE_BEGIN

struct TaskFlowInitParamsG : public CGraph::GParam
{
	std::string taskName_;
	QJsonObject resultJson_;
};

TaskFlowManager::TaskFlowManager()
	: pipeLine_(nullptr)
{

}

TaskFlowManager::~TaskFlowManager()
{
	if (pipeLine_)
	{
		CGraph::GPipelineFactory::remove(pipeLine_);
	}
}

bool TaskFlowManager::Init(const TaskFlowInitParams& parms)
{
	//创建pipeline
	auto pipeLine = TaskFlowFactory::Create(parms);
	if (!pipeLine)
	{
		return false;
	}
	pipeLine_ = *pipeLine;

	//注入全局参数
	pipeLine_->createGParam<TaskFlowInitParamsG>("TaskFlowInitParamsG");
	auto initParams = pipeLine_->getGParam<TaskFlowInitParamsG>("TaskFlowInitParamsG");
	initParams->taskName_ = parms.taskName_;

	return true;
}

bool TaskFlowManager::Run()
{
	if (!pipeLine_)
	{
		return false;
	}
	auto status = pipeLine_->run();
}

QJsonObject TaskFlowManager::GetResult()
{
	auto initParams = pipeLine_->getGParam<TaskFlowInitParamsG>("TaskFlowInitParamsG");
	return initParams->resultJson_;
}

VISSERVICE_NAMESPACE_END