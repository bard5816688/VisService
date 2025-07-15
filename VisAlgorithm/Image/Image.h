#pragma once
#include "HImageStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN

#ifdef USE_HALCON
template<IsImageStrategy Strategy = HImageStrategy>
#else
template<IsRegionStrategy Strategy>
#endif
class ImageContext
{
public:
	ImageContext();
	~ImageContext();
	ImageContext(const ImageContext& other);
	ImageContext& operator=(const ImageContext& other);
	ImageContext(ImageContext&& other) noexcept;
	ImageContext& operator=(ImageContext&& other) noexcept;

	ResultVoid GenImageConst(const char* type, int64_t width, int64_t height);
	ResultVoid GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer);
	ResultVoid GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc);
	ResultVoid GetImageSize(int64_t* width, int64_t* height) const;
	Result<Tuple> CountChannels() const;

private:
	Strategy::Impl* GetImpl() const;
	Strategy strategy_;

	friend class ImageInternalUtils;
};

#ifdef USE_HALCON
#define DEFAULT_IMAGE_STRATEGY HImageStrategy
#elif
#define DEFAULT_IMAGE_STRATEGY "NoSupported"
#endif
using Image = ImageContext<DEFAULT_IMAGE_STRATEGY>;

VISALGORITHM_NAMESPACE_END

#include"Image.inl"