#pragma once
#include "TaskFlowParams.h"
#include "CGraph.h"
#include <any>

VISSERVICE_NAMESPACE_BEGIN

struct TaskFlowInitGParams : public CGraph::GParam
{
	std::string taskName_;
	std::string deputyTaskName_;//副任务名称，包含|
	WorkStation station_;
	AcquisitionType acquisitionType_;
};

VISSERVICE_NAMESPACE_END