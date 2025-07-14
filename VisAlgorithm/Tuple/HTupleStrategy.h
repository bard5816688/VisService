#pragma once

#include "TupleStrategyConcept.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class VisAlgorithmApi HTupleStrategy
{
	class Impl;

public:
	static HTupleStrategy FromVector(const std::vector<TupleElement>& values);

public:
	HTupleStrategy();
	HTupleStrategy(const TupleElement& element);
	~HTupleStrategy();
	HTupleStrategy(const HTupleStrategy& other);
	HTupleStrategy& operator=(const HTupleStrategy& other);
	HTupleStrategy(HTupleStrategy&& other) noexcept;
	HTupleStrategy& operator=(HTupleStrategy&& other) noexcept;

	Impl* GetImpl() const;
	HTupleStrategy& Append(const HTupleStrategy& tuple);
	Result<TupleElementType> Type(size_t idx);
	Result<TupleElement> At(size_t idx) const;

private:
	Impl* impl_;

};

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON