#pragma once

#include "BasicReturnInternal.h"
#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename TupleStrategy>
class TupleHalconUtils
{
public:
	static HalconCpp::HTuple GetHTuple(const TupleStrategy& tuple);
	static TupleStrategy FromHTuple(const HalconCpp::HTuple& hTuple);
	static Result<TupleStrategy> ResultFromHTuple(const Result<HalconCpp::HTuple>& res);
};

extern template class TupleHalconUtils<HTupleStrategy>;

VISALGORITHM_NAMESPACE_END