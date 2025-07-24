#pragma once
#include "TaskFlowParams.h"

namespace CGraph
{
	class GPipeline;
}

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT TaskFlow : public QObject
{
	Q_OBJECT

public:
	TaskFlow();
	~TaskFlow();
	ReturnVoid Initialize(const TaskFlowInitParams& params);
	ReturnVoid Run(const TaskFlowRunParams& params);
	std::any GetResult();

private:
	CGraph::GPipeline* pipeLine_;

};

VISSERVICE_NAMESPACE_END