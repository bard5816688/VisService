#include "HandEyeCalibrationUi.h"

VISSERVICE_NAMESPACE_BEGIN

HandEyeCalibrationUi::HandEyeCalibrationUi(const HandEyeCalibrationInitParams& params_, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

HandEyeCalibrationUi::~HandEyeCalibrationUi()
{}

ReturnVoid HandEyeCalibrationUi::SetPositionCallback(std::function<void(const AxisParams&, const AxisParams&)> callback)
{

}

ReturnVoid HandEyeCalibrationUi::ProcessCalibration(const ProcessHandEyeCalibrationParams& params)
{

}

HandEyeCalibrationResult HandEyeCalibrationUi::GetHandEyeCalibrationResult()
{

}

VISSERVICE_NAMESPACE_END