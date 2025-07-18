#pragma once

#include <QWidget>
#include "ui_ModuleBasicUi.h"
#include "BasicDefs.h"

VISSERVICE_NAMESPACE_BEGIN

class ModuleBasicUi : public QWidget
{
	Q_OBJECT

public:
	ModuleBasicUi(QWidget* parent = nullptr);
	~ModuleBasicUi();

private:
	Ui::ModuleBasicUiClass ui;
};

VISSERVICE_NAMESPACE_END