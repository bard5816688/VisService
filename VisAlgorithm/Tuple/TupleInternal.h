#pragma once

#include "BasicReturnInternal.h"
#include "Tuple.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class TupleInternalUtils
{
public:
	static HalconCpp::HTuple GetHTuple(const Tuple& tuple);
	static Tuple FromHTuple(const HalconCpp::HTuple& hTuple);
	static Result<Tuple> ResultFromHTuple(const Result<HalconCpp::HTuple>& res);
};

VISALGORITHM_NAMESPACE_END

#endif