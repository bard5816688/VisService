#pragma once

#include "HTupleStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsTupleStrategy Strategy = HTupleStrategy>
class Tuple
{
public:
	static Tuple FromVector(const std::vector<TupleElement>& values);

public:
	Tuple();
	Tuple(const TupleElement& element);
	~Tuple();
	Tuple(const Tuple& other);
	Tuple& operator=(const Tuple& other);
	Tuple(Tuple&& other) noexcept;
	Tuple& operator=(Tuple&& other) noexcept;

	Tuple& Append(const Tuple& tuple);
	Result<TupleElementType> Type(size_t idx);
	Result<TupleElement> At(size_t idx) const;

private:
	Strategy strategy_;
};

VISALGORITHM_NAMESPACE_END

#include"Tuple.inl"