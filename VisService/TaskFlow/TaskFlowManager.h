#pragma once
#include "TaskFlowParams.h"

namespace CGraph
{
	class GPipeline;
}

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT TaskFlowManager
{
public:
	TaskFlowManager();
	~TaskFlowManager();
	bool Init(const TaskFlowInitParams& parms);
	bool Run();
	QJsonObject GetResult();

private:
	CGraph::GPipeline* pipeLine_;
	QJsonObject resultJson_;

};

VISSERVICE_NAMESPACE_END