#pragma once

#include <variant>
#include <string>
#include "BasicReturn.h"

VISALGORITHM_NAMESPACE_BEGIN

using TupleElement = std::variant<std::monostate, int, double, std::string>;

enum class TupleElementType
{
	Null,
	Int,
	Double,
	String,
};

class TupleImpl;

class VisAlgorithmApi Tuple
{
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

public:
	static Tuple FromVector(const std::vector<TupleElement>& values);

private:
	TupleImpl* tupleImpl_;

	friend class TupleInternal;
};

VISALGORITHM_NAMESPACE_END