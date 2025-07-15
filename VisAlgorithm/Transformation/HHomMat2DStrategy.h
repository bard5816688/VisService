#pragma once

#include "HomMat2DStrategyConcept.h"

VISALGORITHM_NAMESPACE_BEGIN

class HHomMat2DStrategy
{
public:
	class Impl;
	HHomMat2DStrategy();
	~HHomMat2DStrategy();
	HHomMat2DStrategy(const HHomMat2DStrategy& other);
	HHomMat2DStrategy& operator=(const HHomMat2DStrategy& other);
	HHomMat2DStrategy(HHomMat2DStrategy&& other) noexcept;
	HHomMat2DStrategy& operator=(HHomMat2DStrategy&& other) noexcept;

	Result<HHomMat2DStrategy> HomMat2dTranslate(double tx, double ty) const;

private:
	Impl* impl_;
};

VISALGORITHM_NAMESPACE_END