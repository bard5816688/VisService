#pragma once
#include "TaskFlowParams.h"

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

private:
	Return<std::string> GetTaskName(TaskFlowTopologyType type);

private:
	TaskFlowInitParams params_;

signals:
	void sourceImageReady();
	void runFinished();
	void errorOccurred(const ErrorParams&)

};

VISSERVICE_NAMESPACE_END