#include "TaskFlowUi.h"

VISSERVICE_NAMESPACE_BEGIN

TaskFlowUi::TaskFlowUi(const TaskFlowInitParams& params, QWidget* parent)
	: QWidget(parent)
	, taskFlowInitParams_(params)
	, setPositionFunc_(nullptr)
{
	ui.setupUi(this);
}

TaskFlowUi::~TaskFlowUi()
{}

//ReturnVoid TaskFlowUi::SetPosition(const AxisParams& axis, const AxisParams& camera)
//{
//
//}

ReturnVoid TaskFlowUi::SetPositionCallback(std::function<void(const AxisParams&, const AxisParams&)> callback)
{
	setPositionFunc_ = callback;
}



Return<QPointF> GetMatchingModelCenter(const std::string& taskName_, const std::string& deputyTaskName_)
{

}

VISSERVICE_NAMESPACE_END