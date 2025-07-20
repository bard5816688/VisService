#pragma once
#include "HTupleStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

#ifdef USE_HALCON
template<IsTupleStrategy Strategy>
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
	TupleContext(const Strategy& strategy);
	~TupleContext();
	TupleContext(const TupleContext& other);
	TupleContext& operator=(const TupleContext& other);
	TupleContext(TupleContext&& other) noexcept;
	TupleContext& operator=(TupleContext&& other) noexcept;

	TupleContext& Append(const TupleContext& tuple);
	Result<TupleElementType> Type(size_t idx);
	Result<TupleElement> At(size_t idx) const;
	Result<TupleContext> TupleLength() const;
	Result<TupleContext> TupleSelect(const TupleContext& index) const;
	Result<TupleContext> TupleConcat(const TupleContext& t2) const;
	Result<TupleContext> TupleGenSequence(const TupleContext& start, const TupleContext& end, const TupleContext& step) const;
	Result<TupleContext> TupleGenConst(const TupleContext& length, const TupleContext& Const) const;
	Result<TupleContext> TupleAdd(const TupleContext& s2) const;
	Result<TupleContext> TupleSub(const TupleContext& d2) const;
	Result<TupleContext> TupleMult(const TupleContext& p2) const;
	Result<TupleContext> TupleInsert(const TupleContext& index, TupleContext& invert) const;
	Result<TupleContext> TupleRemove(const TupleContext& index) const;
	Result<TupleContext> TupleReplace(const TupleContext& index, const TupleContext& replacetuple) const;
	Result<TupleContext> TupleDiv(const TupleContext& q2) const;
	Result<TupleContext> TuplePow(const TupleContext& t2) const;
	Result<TupleContext> TupleAbs() const;
	Result<TupleContext> TupleSqrt() const;
	Result<TupleContext> TupleRound() const;
	Result<TupleContext> TupleMean() const;
	Result<TupleContext> TupleSum() const;
	Result<TupleContext> TupleMax() const;
	Result<TupleContext> TupleMin() const;
	Result<TupleContext> TupleGreater(const TupleContext& t2) const;
	Result<TupleContext> TupleLess(const TupleContext& t2) const;
	Result<TupleContext> TupleEqual(const TupleContext& t2) const;
	Result<TupleContext> TupleAnd(const TupleContext& t2) const;
	Result<TupleContext> TupleOr(const TupleContext& t2) const;
	Result<TupleContext> TupleNot() const;
	Result<TupleContext> TupleString(const TupleContext& format) const;
	Result<TupleContext> TupleNumber() const;
	Result<TupleContext> TupleSplit(const TupleContext& separator) const;
	Result<TupleContext> TupleJoin(const TupleContext& separators) const;
	Result<TupleContext> TupleInt() const;
	Result<TupleContext> TupleReal() const;
	Result<TupleContext> ReadTuple(const TupleContext& filename) const;
	ResultVoid WriteTuple(const TupleContext& filename) const;
	Result<TupleContext> TupleUnion(const TupleContext& set2) const;
	Result<TupleContext> TupleIntersection(const TupleContext& set2) const;
	Result<TupleContext> TupleDifference(const TupleContext& set2) const;
	Result<TupleContext> TupleSort() const;
	Result<TupleContext> TupleSortIndex() const;

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