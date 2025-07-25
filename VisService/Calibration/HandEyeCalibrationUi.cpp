#include "HandEyeCalibrationUi.h"

VISSERVICE_NAMESPACE_BEGIN

HandEyeCalibrationUi::HandEyeCalibrationUi(const HandEyeCalibrationInitParams& params_, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

HandEyeCalibrationUi::~HandEyeCalibrationUi()
{}

ReturnVoid HandEyeCalibrationUi::SetPosition(const AxisParams& axis, const AxisParams& camera)
{

}

ReturnVoid HandEyeCalibrationUi::ProcessCalibration(const ProcessHandEyeCalibrationParams& params)
{

}

HandEyeCalibrationResult HandEyeCalibrationUi::GetHandEyeCalibrationResult()
{

}

VISSERVICE_NAMESPACE_END