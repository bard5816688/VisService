#pragma once

#include "BasicReturn.h"
#include "Tuple.h"

VISALGORITHM_NAMESPACE_BEGIN

class RegionImpl;

class VisAlgorithmApi Region
{
public:
	Region();
	Region(double row1, double column1, double row2, double column2);
	Region(double row, double column, double radius);
	~Region();
	Region(const Region& other);
	Region& operator=(const Region& other);
	Region(Region&& other) noexcept;
	Region& operator=(Region&& other) noexcept;

	Result<int64_t> AreaCenter(double* row, double* column) const;

#ifdef VISALGORITHM_EXPORTS
	RegionImpl* ImplPtr() const;
#endif
private:
	RegionImpl* regionImpl_;
};

VISALGORITHM_NAMESPACE_END

