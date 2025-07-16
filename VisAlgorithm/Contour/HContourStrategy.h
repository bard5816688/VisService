#pragma once

#include "ContourStrategyConcept.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class VisAlgorithmApi HContourStrategy
{
public:
	class Impl;
	HContourStrategy();
	~HContourStrategy();
	HContourStrategy(const HContourStrategy& other);
	HContourStrategy& operator=(const HContourStrategy& other);
	HContourStrategy(HContourStrategy&& other) noexcept;
	HContourStrategy& operator=(HContourStrategy&& other) noexcept;


public:
	Impl* GetImpl() const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif