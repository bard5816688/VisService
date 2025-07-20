#pragma once
#include "TupleStrategyConcept.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class VisAlgorithmApi HTupleStrategy
{
public:
	class Impl;
	static HTupleStrategy FromVector(const std::vector<TupleElement>& values);

public:
	HTupleStrategy();
	HTupleStrategy(const TupleElement& element);
	~HTupleStrategy();
	HTupleStrategy(const HTupleStrategy& other);
	HTupleStrategy& operator=(const HTupleStrategy& other);
	HTupleStrategy(HTupleStrategy&& other) noexcept;
	HTupleStrategy& operator=(HTupleStrategy&& other) noexcept;

	HTupleStrategy& Append(const HTupleStrategy& tuple);
	Result<TupleElementType> Type(size_t idx);
	Result<TupleElement> At(size_t idx) const;
	Result<HTupleStrategy> TupleLength() const;
	Result<HTupleStrategy> TupleSelect(const HTupleStrategy& index) const;
	Result<HTupleStrategy> TupleConcat(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleGenSequence(const HTupleStrategy& start, const HTupleStrategy& end, const HTupleStrategy& step) const;
	Result<HTupleStrategy> TupleGenConst(const HTupleStrategy& length, const HTupleStrategy& Const) const;
	Result<HTupleStrategy> TupleAdd(const HTupleStrategy& s2) const;
	Result<HTupleStrategy> TupleSub(const HTupleStrategy& d2) const;
	Result<HTupleStrategy> TupleMult(const HTupleStrategy& p2) const;
	Result<HTupleStrategy> TupleInsert(const HTupleStrategy& index, HTupleStrategy& invert) const;
	Result<HTupleStrategy> TupleRemove(const HTupleStrategy& index) const;
	Result<HTupleStrategy> TupleReplace(const HTupleStrategy& index, const HTupleStrategy& replacetuple) const;
	Result<HTupleStrategy> TupleDiv(const HTupleStrategy& q2) const;
	Result<HTupleStrategy> TuplePow(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleAbs() const;
	Result<HTupleStrategy> TupleSqrt() const;
	Result<HTupleStrategy> TupleRound() const;
	Result<HTupleStrategy> TupleMean() const;
	Result<HTupleStrategy> TupleSum() const;
	Result<HTupleStrategy> TupleMax() const;
	Result<HTupleStrategy> TupleMin() const;
	Result<HTupleStrategy> TupleGreater(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleLess(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleEqual(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleAnd(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleOr(const HTupleStrategy& t2) const;
	Result<HTupleStrategy> TupleNot() const;
	Result<HTupleStrategy> TupleString(const HTupleStrategy& format) const;
	Result<HTupleStrategy> TupleNumber() const;
	Result<HTupleStrategy> TupleSplit(const HTupleStrategy& separator) const;
	Result<HTupleStrategy> TupleJoin(const HTupleStrategy& separators) const;
	Result<HTupleStrategy> TupleInt() const;
	Result<HTupleStrategy> TupleReal() const;
	Result<HTupleStrategy> ReadTuple(const HTupleStrategy& filename) const;
	ResultVoid WriteTuple(const HTupleStrategy& filename) const;
	Result<HTupleStrategy> TupleUnion(const HTupleStrategy& set2) const;
	Result<HTupleStrategy> TupleIntersection(const HTupleStrategy& set2) const;
	Result<HTupleStrategy> TupleDifference(const HTupleStrategy& set2) const;
	Result<HTupleStrategy> TupleSort() const;
	Result<HTupleStrategy> TupleSortIndex() const;

public:
	Impl* GetImpl() const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON