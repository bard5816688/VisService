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
	OtfAcquisition,//飞拍
};

struct TaskFlowStation
{
	int cameraNum_;
	int stationNum_;
};

struct TaskFlowInitParams
{
	std::string taskName_;
	std::string deputyTaskName_;//副任务名称，包含|
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