#pragma once

#include "HalconCpp.h"
#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HTuple GetHTuple(const Tuple& tuple);
Tuple FromHTuple(const HalconCpp::HTuple& hTuple);

VISALGORITHM_NAMESPACE_END