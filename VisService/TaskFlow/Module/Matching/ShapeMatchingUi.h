#pragma once
#include <QWidget>
#include "ui_ShapeMatchingUi.h"
#include "ShapeMatchingParams.h"

VISSERVICE_NAMESPACE_BEGIN

class ShapeMatchingUi : public ModuleUiBase
{
	Q_OBJECT

public:
	ShapeMatchingUi(const std::string& taskName, QWidget* parent);
	~ShapeMatchingUi();
	virtual std::string GetModuleName() override;

private:
	Ui::ShapeMatchingUiClass ui;

};

VISSERVICE_NAMESPACE_END