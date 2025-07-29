#pragma once

#include <QWidget>
#include "ui_ShapeMatchingUi.h"
#include "ShapeMatchingParams.h"

VISSERVICE_NAMESPACE_BEGIN

class ShapeMatchingUi : public QWidget
{
	Q_OBJECT

public:
	ShapeMatchingUi(QWidget *parent = nullptr);
	~ShapeMatchingUi();

private:
	Ui::ShapeMatchingUiClass ui;

};

VISSERVICE_NAMESPACE_END