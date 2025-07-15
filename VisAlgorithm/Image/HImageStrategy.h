#pragma once
#include "ImageStrategyConcept.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class VisAlgorithmApi HImageStrategy
{
public:
	class Impl;
	HImageStrategy();
	~HImageStrategy();
	HImageStrategy(const HImageStrategy& other);
	HImageStrategy& operator=(const HImageStrategy& other);
	HImageStrategy(HImageStrategy&& other) noexcept;
	HImageStrategy& operator=(HImageStrategy&& other) noexcept;

	ResultVoid GenImageConst(const char* type, int64_t width, int64_t height);
	ResultVoid GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer);
	ResultVoid GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc);
	ResultVoid GetImageSize(int64_t* width, int64_t* height) const;
	Result<Tuple> CountChannels() const;

public:
	Impl* GetImpl() const;

private:
	Impl* impl_;
};

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON