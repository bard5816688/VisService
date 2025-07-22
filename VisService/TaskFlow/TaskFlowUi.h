#pragma once
#include <QWidget>
#include "ui_TaskFlowUi.h"
#include "BasicDefs.h"

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowUi : public QWidget
{
	Q_OBJECT

public:
	TaskFlowUi(QWidget *parent = nullptr);
	~TaskFlowUi();

private:
	Ui::TaskFlowUiClass ui;
};

VISSERVICE_NAMESPACE_END