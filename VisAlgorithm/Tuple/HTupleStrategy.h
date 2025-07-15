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

public:
	Impl* GetImpl() const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON