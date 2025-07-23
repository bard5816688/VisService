#pragma once
#include "TaskFlowParams.h"

namespace CGraph
{
	class GPipeline;
}

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT TaskFlow
{
public:
	TaskFlow();
	~TaskFlow();
	ReturnVoid Initialize(const TaskFlowInitParams& params);
	ReturnVoid Run(const TaskFlowRunParams& params);


private:
	CGraph::GPipeline* pipeLine_;

};

VISSERVICE_NAMESPACE_END