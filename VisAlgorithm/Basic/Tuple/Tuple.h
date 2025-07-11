#pragma once

#include "VisAlgorithmDefs.h"

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
	TupleElementType Type(size_t idx);

	template<typename T>
		requires std::is_arithmetic_v<T> || std::is_same_v<T, std::string>
	T Get(size_t index) const;

public:
	static Tuple FromVector(const std::vector<TupleElement>& values);

#ifdef VISALGORITHM_EXPORTS
	TupleImpl* ImplPtr() const;
#endif
private:
	TupleElement At(size_t index) const;

private:
	TupleImpl* tupleImpl_;

};

VISALGORITHM_NAMESPACE_END

#include "Tuple.inl"