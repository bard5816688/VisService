#include "TaskFlowUi.h"
#include "TaskFlowBuilder.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlowUi::TaskFlowUi(QWidget* parent)
	: QWidget(parent)

{
	ui.setupUi(this);
}

TaskFlowUi::~TaskFlowUi()
{}

ReturnVoid TaskFlowUi::Initialize(const TaskFlowInitParams& params)
{
	taskFlowInitParams_ = params;
	SetupUi(this);
}

ReturnVoid TaskFlowUi::SetPosition(const AxisParams& axis, const AxisParams& camera)
{
	return ReturnVoid();
}

ReturnVoid TaskFlowUi::SetupUi(QWidget* parent)
{

}

Return<MatchingModelInformation> GetMatchingModelInformation(const std::string& taskName_, const std::string& deputyTaskName_)
{
	return Return<MatchingModelInformation>();
}



VISSERVICE_NAMESPACE_END