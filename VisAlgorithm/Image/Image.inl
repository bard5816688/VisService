#pragma once
#include "Image.h"

VISALGORITHM_NAMESPACE_BEGIN

template<IsImageStrategy Strategy>
ImageContext<Strategy>::ImageContext()
{

}

template<IsImageStrategy Strategy>
inline ImageContext<Strategy>::~ImageContext()
{

}

template<IsImageStrategy Strategy>
inline ImageContext<Strategy>::ImageContext(const ImageContext<Strategy>& other)
	: strategy_(other.strategy_)
{

}

template<IsImageStrategy Strategy>
inline ImageContext<Strategy>& ImageContext<Strategy>::operator=(const ImageContext<Strategy>& other)
{
	if (this != &other) {
		strategy_ = other.strategy_;
	}
	return *this;
}

template<IsImageStrategy Strategy>
inline ImageContext<Strategy>::ImageContext(ImageContext&& other) noexcept
	: strategy_(std::move(other.strategy_))
{
}

template<IsImageStrategy Strategy>
inline ImageContext<Strategy>& ImageContext<Strategy>::operator=(ImageContext<Strategy>&& other) noexcept
{
	if (this != &other) {
		strategy_ = std::move(other.strategy_);
	}
	return *this;
}

template<IsImageStrategy Strategy>
ResultVoid ImageContext<Strategy>::GenImageConst(const char* type, int64_t width, int64_t height)
{
	return strategy_.GenImageConst(type, width, height);
}

template<IsImageStrategy Strategy>
ResultVoid ImageContext<Strategy>::GenImage1(const char* type, int64_t width, int64_t height, void* pixelPointer)
{
	return strategy_.GenImage1(type, width, height, pixelPointer);
}

template<IsImageStrategy Strategy>
ResultVoid ImageContext<Strategy>::GenImage1Extern(const char* type, int64_t width, int64_t height, void* pixelPointer, ClearProc clearProc)
{
	return strategy_.GenImage1Extern(type, width, height, pixelPointer, clearProc);
}

template<IsImageStrategy Strategy>
ResultVoid ImageContext<Strategy>::GetImageSize(int64_t* width, int64_t* height) const
{
	return strategy_.GetImageSize(width, height	);
}

template<IsImageStrategy Strategy>
Result<Tuple> ImageContext<Strategy>::CountChannels() const
{
	return strategy_.CountChannels();
}

template<IsImageStrategy Strategy>
Strategy::Impl* ImageContext<Strategy>::GetImpl() const
{
	return strategy_.GetImpl();
}

VISALGORITHM_NAMESPACE_END