#pragma once
#include "TaskFlowParams.h"
#include "CGraph.h"
#include <any>

VISSERVICE_NAMESPACE_BEGIN

struct TaskFlowInitGParams : public CGraph::GParam
{
	std::string taskName_;
	std::string deputyTaskName_;//���������ƣ�����|
	TaskFlowStation station_;
	TaskFlowAcquisitionType acquisitionType_;
};

VISSERVICE_NAMESPACE_END