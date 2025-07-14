#pragma once

#include "BasicReturn.h"
#include "Tuple.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageImpl;

class VisAlgorithmApi Image
{
	using ClearProc = void(__cdecl*)(void*);

public:
	Image();
	~Image();
	Image(const Image& other);
	Image& operator=(const Image& other);
	Image(Image&& other) noexcept;
	Image& operator=(Image&& other) noexcept;

	ResultVoid GenImageConst(const char* type, int64_t width, int64_t height);
	ResultVoid GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer);
	ResultVoid GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc);
	Result<Tuple> Width();
	Result<Tuple> Height();
	Result<Tuple> CountChannels() const;

private:
	ImageImpl* imageImpl_;

	friend class ImageInternal;
};

VISALGORITHM_NAMESPACE_END