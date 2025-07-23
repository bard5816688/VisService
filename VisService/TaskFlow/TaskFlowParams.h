#pragma once
#include "../Basic/BasicObject.h"
#include "VisAlgorithm.h"

VISSERVICE_NAMESPACE_BEGIN

enum class TaskFlowTopologyType
{
	DispensingMatching,
	PostDispensingInspectionNormal,

};

enum class TaskFlowAcquisitionType
{
	StaticAcquisition,
	OtfAcquisition,//����
};

struct TaskFlowStation
{
	int cameraNum_;
	int stationNum_;
};

struct TaskFlowInitParams
{
	std::string taskName_;
	std::string deputyTaskName_;//���������ƣ�����|
	TaskFlowStation station_;
	TaskFlowAcquisitionType acquisitionType_;
	TaskFlowTopologyType topologyType_;
};

struct TaskFlowRunParams
{
	AxisParams axisParams_;
};

struct DispensingMatchingTaskFlowResultPrams
{
	VisAlgorithm::Image srcImage_;

};



VISSERVICE_NAMESPACE_END