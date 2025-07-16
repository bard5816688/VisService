#pragma once
#include "HContourStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

#ifdef USE_HALCON
template<IsContourStrategy Strategy = HContourStrategy>
#else
template<IsRegionStrategy Strategy>
#endif
class ContourContext
{
public:
	ContourContext();
	~ContourContext();
	ContourContext(const ContourContext& other);
	ContourContext& operator=(const ContourContext& other);
	ContourContext(ContourContext&& other) noexcept;
	ContourContext& operator=(ContourContext&& other) noexcept;

private:
	Strategy::Impl* GetImpl() const;
	Strategy strategy_;

	friend class ContourInternalUtils;
};

#ifdef USE_HALCON
#define DEFAULT_CONTOUR_STRATEGY HContourStrategy
#elif
#define DEFAULT_CONTOUR_STRATEGY "NoSupported"
#endif
using Contour = ContourContext<DEFAULT_CONTOUR_STRATEGY>;

VISALGORITHM_NAMESPACE_END

#include"Contour.inl"