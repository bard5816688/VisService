#pragma once
#include <QWidget>
#include "ui_TaskFlowUi.h"
#include "TaskFlowParams.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT TaskFlowUi : public QWidget
{
	Q_OBJECT

public:
	TaskFlowUi(const TaskFlowInitParams& params, QWidget* parent = nullptr);
	~TaskFlowUi();
	ReturnVoid SetPosition(const AxisParams& axis, const AxisParams& camera);

signals:
	void referenceImageDeterminded();
	void matchingModelFinished(bool);
	void requestMotionControlWidget(const QPoint& _point);

private:
	Ui::TaskFlowUiClass ui;
	TaskFlowInitParams taskFlowInitParams_;

};

VISSERVICE_EXPORT Return<MatchingModelInformation> GetMatchingModelInformation(const std::string& taskName_, const std::string& deputyTaskName_);

VISSERVICE_NAMESPACE_END