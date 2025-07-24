#pragma once
#pragma once
#include "../Basic/BasicObject.h"
#include "VisAlgorithm.h"

VISSERVICE_NAMESPACE_BEGIN

struct HandEyeCalibrationInitParams
{
	WorkStation station_;
};

struct ProcessHandEyeCalibrationParams
{
	std::vector<VisAlgorithm::Image> images_;
	std::vector<AxisParams> axisPfs_;
	std::vector<AxisParams> cameraPfs_;
};

struct HandEyeCalibrationResult
{
	std::vector<double> handEyeMat_;
	QPointF pixelResolution_;
};


VISSERVICE_NAMESPACE_END