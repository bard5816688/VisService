#include "ImageInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class ImageImpl
{
public:
	HalconCpp::HImage hImage_;
};



HalconCpp::HImage GetHImage(const Image& image)
{

}

Image FromHImage(const HalconCpp::HImage& hImage)
{

}

VISALGORITHM_NAMESPACE_END