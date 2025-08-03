#pragma once
#include <QWidget>
#include "ui_TaskFlowUi.h"
#include "TaskFlowParams.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT TaskFlowUi : public QWidget
{
	Q_OBJECT

public:
	TaskFlowUi(QWidget* parent = nullptr);
	~TaskFlowUi();
	ReturnVoid Initialize(const TaskFlowInitParams& params);
	ReturnVoid SetPosition(const AxisParams& axis, const AxisParams& camera);

	     
private:
	ReturnVoid SetupUi(QWidget* parent);


private:
	Ui::TaskFlowUiClass ui;
	TaskFlowInitParams taskFlowInitParams_;

signals:
	void ReferenceImageDeterminded();
	void MatchingModelFinished(bool);
	void RequestMotionControlWidget(const QPoint& _point);

};

VISSERVICE_EXPORT Return<MatchingModelInformation> GetMatchingModelInformation(const std::string& taskName_, const std::string& deputyTaskName_);

VISSERVICE_NAMESPACE_END