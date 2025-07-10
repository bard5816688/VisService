#pragma once

#include "VisAlgorithmDefs.h"
#include "HTuple.h"

VISALGORITHM_NAMESPACE_BEGIN

using TupleElement = std::variant
<
	std::monostate,
	int,
	double,
	std::string,
>;

enum class TupleElementType
{
	Null,
	Int,
	Double,
	String,
};

struct TupleImpl;
using TupleImplPtr = std::shared_ptr<TupleImpl>;

class Tuple
{
public:
	Tuple();
	Tuple(const TupleElement& value);
	~Tuple();
	Tuple& Append(const Tuple& tuple);
	TupleElementType Type(size_t idx);
	template<typename T>
		requires std::is_arithmetic_v<T> || std::is_same_v<T, std::string>
	T At(size_t index) const;

public:
	static Tuple FromVector(const std::vector<TupleElement>& values);

#ifdef VISALGORITHM_EXPORTS
	TupleImplPtr ImplPtr() const;
#endif
private:
	TupleImplPtr tupleImpl_;

};

VISALGORITHM_NAMESPACE_END

#include "Tuple.inl"