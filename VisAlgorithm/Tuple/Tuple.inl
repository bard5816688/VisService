#pragma once

#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy> TupleContext<Strategy>::FromVector(const std::vector<TupleElement>& values)
{
	return Strategy::FromVector(values);
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext()
{

}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(const TupleElement& element)
{
	strategy_.Append(element);
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(const Strategy& strategy)
	: strategy_(strategy)
{
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::~TupleContext()
{

}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(const TupleContext<Strategy>& other)
	: strategy_(other.strategy_)
{

}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>& TupleContext<Strategy>::operator=(const TupleContext<Strategy>& other)
{
	if (this != &other)
	{
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>::TupleContext(TupleContext&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsTupleStrategy Strategy>
inline TupleContext<Strategy>& TupleContext<Strategy>::operator=(TupleContext<Strategy>&& other) noexcept
{
	if (this != &other)
	{
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsTupleStrategy Strategy>
inline Strategy::Impl* TupleContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

template<IsTupleStrategy Strategy>
TupleContext<Strategy>& TupleContext<Strategy>::Append(const TupleContext<Strategy>& tuple)
{
	strategy_.Append(tuple.strategy_);
	return *this;
}

template<IsTupleStrategy Strategy>
Result<TupleElementType> TupleContext<Strategy>::Type(size_t idx)
{
	return strategy_.Type(idx);
}

template<IsTupleStrategy Strategy>
Result<TupleElement> TupleContext<Strategy>::At(size_t idx) const
{
	return strategy_.At(idx);
}

template<IsTupleStrategy Strategy>
Result<int64_t> TupleContext<Strategy>::Length() const
{
	return strategy_.Length();
}
template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSelect(const TupleContext<Strategy>& index) const
{
	return strategy_.TupleSelect(index.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleConcat(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleConcat(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleGenSequence(const TupleContext<Strategy>& start, const TupleContext<Strategy>& end, const TupleContext<Strategy>& step) const
{
	return strategy_.TupleGenSequence(start.strategy_, end.strategy_, step.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleGenConst(const TupleContext<Strategy>& length, const TupleContext<Strategy>& Const) const
{
	return strategy_.TupleGenConst(length.strategy_, Const.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleAdd(const TupleContext<Strategy>& s2) const
{
	return strategy_.TupleAdd(s2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSub(const TupleContext<Strategy>& d2) const
{
	return strategy_.TupleSub(d2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleMult(const TupleContext<Strategy>& p2) const
{
	return strategy_.TupleMult(p2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleInsert(const TupleContext<Strategy>& index, TupleContext<Strategy>& invert) const
{
	return strategy_.TupleInsert(index.strategy_, invert.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleRemove(const TupleContext<Strategy>& index) const
{
	return strategy_.TupleRemove(index.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleReplace(const TupleContext<Strategy>& index, const TupleContext<Strategy>& replacetuple) const
{
	return strategy_.TupleReplace(index.strategy_, replacetuple.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleDiv(const TupleContext<Strategy>& q2) const
{
	return strategy_.TupleDiv(q2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TuplePow(const TupleContext<Strategy>& t2) const
{
	return strategy_.TuplePow(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleAbs() const
{
	return strategy_.TupleAbs();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSqrt() const
{
	return strategy_.TupleSqrt();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleRound() const
{
	return strategy_.TupleRound();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleMean() const
{
	return strategy_.TupleMean();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSum() const
{
	return strategy_.TupleSum();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleMax() const
{
	return strategy_.TupleMax();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleMin() const
{
	return strategy_.TupleMin();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleGreater(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleGreater(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleLess(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleLess(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleEqual(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleEqual(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleAnd(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleAnd(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleOr(const TupleContext<Strategy>& t2) const
{
	return strategy_.TupleOr(t2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleNot() const
{
	return strategy_.TupleNot();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleString(const TupleContext<Strategy>& format) const
{
	return strategy_.TupleString(format.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleNumber() const
{
	return strategy_.TupleNumber();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSplit(const TupleContext<Strategy>& separator) const
{
	return strategy_.TupleSplit(separator.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleJoin(const TupleContext<Strategy>& separators) const
{
	return strategy_.TupleJoin(separators.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleInt() const
{
	return strategy_.TupleInt();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleReal() const
{
	return strategy_.TupleReal();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::ReadTuple(const TupleContext<Strategy>& filename) const
{
	return strategy_.ReadTuple(filename.strategy_);
}

template<IsTupleStrategy Strategy>
ResultVoid TupleContext<Strategy>::WriteTuple(const TupleContext<Strategy>& filename) const
{
	return strategy_.WriteTuple(filename.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleUnion(const TupleContext<Strategy>& set2) const
{
	return strategy_.TupleUnion(set2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleIntersection(const TupleContext<Strategy>& set2) const
{
	return strategy_.TupleIntersection(set2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleDifference(const TupleContext<Strategy>& set2) const
{
	return strategy_.TupleDifference(set2.strategy_);
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSort() const
{
	return strategy_.TupleSort();
}

template<IsTupleStrategy Strategy>
Result<TupleContext<Strategy>> TupleContext<Strategy>::TupleSortIndex() const
{
	return strategy_.TupleSortIndex();
}

VISALGORITHM_NAMESPACE_END