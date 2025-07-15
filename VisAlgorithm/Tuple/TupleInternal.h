#pragma once

#include "BasicReturnInternal.h"
#include "Tuple.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

template<IsTupleStrategy TupleStrategy>
class TupleInternalUtils
{
public:
	static HalconCpp::HTuple GetHTuple(const TupleStrategy& tuple);
	static TupleStrategy FromHTuple(const HalconCpp::HTuple& hTuple);
	static Result<TupleStrategy> ResultFromHTuple(const Result<HalconCpp::HTuple>& res);
};

extern template class TupleInternalUtils<HTupleStrategy>;

VISALGORITHM_NAMESPACE_END

#endif