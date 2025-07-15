#pragma once

#include "HTupleStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN
#ifdef USE_HALCON
template<IsTupleStrategy Strategy = HTupleStrategy>
#else
template<IsTupleStrategy Strategy>
#endif
class TupleContext
{
public:
	static TupleContext FromVector(const std::vector<TupleElement>& values);

public:
	TupleContext();
	TupleContext(const TupleElement& element);
	~TupleContext();
	TupleContext(const TupleContext& other);
	TupleContext& operator=(const TupleContext& other);
	TupleContext(TupleContext&& other) noexcept;
	TupleContext& operator=(TupleContext&& other) noexcept;

	TupleContext& Append(const TupleContext& tuple);
	Result<TupleElementType> Type(size_t idx);
	Result<TupleElement> At(size_t idx) const;

private:
	Strategy::Impl* GetImpl() const;
	Strategy strategy_;

	friend class TupleInternalUtils;
};


#ifdef USE_HALCON
#define DEFAULT_TUPLE_STRATEGY HTupleStrategy
#elif
#define DEFAULT_TUPLE_STRATEGY "NoSupported"
#endif
using Tuple = TupleContext<DEFAULT_TUPLE_STRATEGY>;

VISALGORITHM_NAMESPACE_END

#include"Tuple.inl"