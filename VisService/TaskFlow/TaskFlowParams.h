#pragma once
#include "../Basic/BasicReturn.h"
#include <QJsonObject>

VISSERVICE_NAMESPACE_BEGIN

enum class TaskFlowTopologyType
{
	DispensingMatching,
	PostDispensingInspectionNormal,

};

struct TaskFlowInitParams
{
	std::string taskName_;
};


VISSERVICE_NAMESPACE_END