#pragma once

#include <QWidget>
#include "ui_PipeLineTeachUi.h"
#include "BasicDefs.h"

VISSERVICE_NAMESPACE_BEGIN

class PipeLineTeachUi : public QWidget
{
	Q_OBJECT

public:
	PipeLineTeachUi(QWidget *parent = nullptr);
	~PipeLineTeachUi();

private:
	Ui::PipeLineTeachUiClass ui;
};

VISSERVICE_NAMESPACE_END