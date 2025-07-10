#pragma once

#include "VisAlgorithmDefs.h"
#include "Tuple.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageImpl;
using ImageImplPtr = std::shared_ptr<ImageImpl>;

class Image
{
public:
	Image();
	Image(const char* type, uint32_t width, uint32_t height);
	Image(const char* type, int64_t width, int64_t height, void* pixelPointer);
	~Image();
	int64_t Width();
	int64_t Height();
	std::shared_ptr<uint8_t> Data();
	std::string Format();
	//Tuple CountChannls() const;


#ifdef VISALGORITHM_EXPORTS
	ImageImplPtr ImplPtr() const;
#endif
private:
	ImageImplPtr imageImpl_;
};

VISALGORITHM_NAMESPACE_END