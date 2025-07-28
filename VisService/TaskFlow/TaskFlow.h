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
	ReturnVoid AsyncRun(const TaskFlowRunParams& params);
	Return<QJsonObject> GetResult();
	Return<VisAlgorithm::Image> GetSourceImage();
	Return<VisAlgorithm::Image> GetResultImage();

signals:
	void sourceImageReady();
	void runFinished();
	void errorOccurred(const ErrorParams&);

private:
	CGraph::GPipeline* pipeLine_;

};

VISSERVICE_NAMESPACE_END