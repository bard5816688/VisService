#include "TaskFlowUi.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlowUi::TaskFlowUi(const TaskFlowInitParams& params, QWidget* parent)
	: QWidget(parent)
	, taskFlowInitParams_(params)
{
	ui.setupUi(this);
}

TaskFlowUi::~TaskFlowUi()
{}

ReturnVoid TaskFlowUi::SetPosition(const AxisParams& axis, const AxisParams& camera)
{
	return ReturnVoid();
}

Return<MatchingModelInformation> GetMatchingModelInformation(const std::string& taskName_, const std::string& deputyTaskName_)
{
	return Return<MatchingModelInformation>();
}

VISSERVICE_NAMESPACE_END