#pragma once
#include "TaskFlowParams.h"
#include "CGraph.h"
#include <any>

VISSERVICE_NAMESPACE_BEGIN

struct TaskFlowInitGParams : public CGraph::GParam
{
	std::string taskName_;
	std::string deputyTaskName_;//副任务名称，包含|
	TaskFlowStation station_;
	TaskFlowAcquisitionType acquisitionType_;
};

struct TaskFlowNodeIoGParams : public CGraph::GParam
{
	struct Param
	{
		std::any data_;
		std::string type_;
	};
	std::map<std::string, std::map<std::string, Param>> nodeIoParms_;
};

VISSERVICE_NAMESPACE_END