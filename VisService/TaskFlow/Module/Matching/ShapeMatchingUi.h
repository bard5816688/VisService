#pragma once

#include <QWidget>
#include "ui_ShapeMatchingUi.h"

class ShapeMatchingUi : public QWidget
{
	Q_OBJECT

public:
	ShapeMatchingUi(QWidget *parent = nullptr);
	~ShapeMatchingUi();

private:
	Ui::ShapeMatchingUiClass ui;
};

