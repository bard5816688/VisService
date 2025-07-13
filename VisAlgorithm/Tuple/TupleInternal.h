#pragma once

#include "BasicReturnInternal.h"
#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

HalconCpp::HTuple GetHTuple(const Tuple& tuple);
Tuple FromHTuple(const HalconCpp::HTuple& hTuple);
Result<Tuple> ResultFromHTuple(const Result<HalconCpp::HTuple>& result);

VISALGORITHM_NAMESPACE_END