#pragma once
#include "../Basic/BasicObject.h"
#include "VisAlgorithm.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

enum class TaskFlowTopologyType
{
	DispensingMatching,
	PostDispensingInspectionNormal,

};

struct TaskFlowInitParams
{
	std::string taskName_;
	std::string deputyTaskName_;	//副任务名称，包含|
	WorkStation station_;
	AcquisitionType acquisitionType_;
	TaskFlowTopologyType topologyType_;
};

struct TaskFlowRunParams
{
	AxisParams axisParams_;
};

struct MatchingModelInformation
{
	QPointF modelCenterPt_;
};



VISSERVICE_NAMESPACE_END