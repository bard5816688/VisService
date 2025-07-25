#pragma once

#include <QWidget>
#include "ui_HandEyeCalibrationUi.h"
#include "CalibrationParams.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT HandEyeCalibrationUi : public QWidget
{
	Q_OBJECT

public:
	HandEyeCalibrationUi(const HandEyeCalibrationInitParams& params_, QWidget* parent = nullptr);
	~HandEyeCalibrationUi();
	ReturnVoid SetPosition(const AxisParams& axis, const AxisParams& camera);
	ReturnVoid ProcessCalibration(const ProcessHandEyeCalibrationParams& params);
	HandEyeCalibrationResult GetHandEyeCalibrationResult();

signals:
	void requestMotionControlWidget(const QPoint&);
	void move2CalibrationPosition();
	void startCalibration(const std::vector<AxisParams>&);

private:
	Ui::HandEyeCalibrationUiClass ui;

};

VISSERVICE_NAMESPACE_END