#pragma once

#include "Tuple.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageImpl;

class VisAlgorithmApi Image
{
	using ClearProc = void(__cdecl*)(void*);

public:
	Image();
	Image(const char* type, int64_t width, int64_t height);
	Image(const char* type, int64_t width, int64_t height, void* pixelPointer);
	Image(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc);
	~Image();
	Image(const Image& other);
	Image& operator=(const Image& other);
	Image(Image&& other) noexcept;
	Image& operator=(Image&& other) noexcept;
	Tuple Width();
	Tuple Height();
	Tuple CountChannels() const;


#ifdef VISALGORITHM_EXPORTS
	ImageImpl* ImplPtr() const;
#endif
private:
	ImageImpl* imageImpl_;
};

VISALGORITHM_NAMESPACE_END