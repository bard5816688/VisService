#pragma once
#include <QWidget>
#include "ui_PipeLineUi.h"
#include "../../Basic/BasicObject.h"

VISSERVICE_NAMESPACE_BEGIN

class ModuleUiBase;
class PipeLineUi : public QWidget
{
	Q_OBJECT

public:
	PipeLineUi(QWidget *parent = nullptr);
	~PipeLineUi();
	ReturnVoid RegisterModule(ModuleUiBase* nodePtr, const std::string& moduleName = "");

private:


private:
	Ui::PipeLineUiClass ui;

};

VISSERVICE_NAMESPACE_END