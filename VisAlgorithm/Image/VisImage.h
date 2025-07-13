#pragma once

#include "VisAlgorithmDefs.h"

VISALGORITHM_NAMESPACE_BEGIN

enum class PixelFormat
{
	Mono8,     ///< 8位灰度图像
	Mono10,    ///< 10位灰度图像
	Mono12,    ///< 12位灰度图像
	Mono16,    ///< 16位灰度图像
	Rgb8,      ///< 24位RGB彩色图像
	Bgr8,      ///< 24位BGR彩色图像
	Rgba8,     ///< 32位RGBA彩色图像
	Bgra8,     ///< 32位BGRA彩色图像
	BayerRg8,  ///< 8位Bayer RG格式
	BayerGb8,  ///< 8位Bayer GB格式
	BayerGr8,  ///< 8位Bayer GR格式
	BayerBg8,  ///< 8位Bayer BG格式
	Unknown    ///< 未知格式
};

class VisImage
{
public:
	VisImage();
	VisImage(uint32_t width, uint32_t height, PixelFormat format);
	~VisImage();

	static int GetBytesPerPixel(PixelFormat format);

protected:
	uint32_t width_;                                  ///< 图像宽度
	uint32_t height_;                                 ///< 图像高度
	PixelFormat pixelFormat_;                         ///< 像素格式
	std::shared_ptr<uint8_t> data_;                   ///< 图像数据
	size_t dataSize_;                                 ///< 数据大小
	uint64_t frameId_;                                ///< 帧ID
	std::chrono::system_clock::time_point timestamp_; ///< 时间戳
	std::string cameraSerialNumber_;                  ///< 相机序列号
};

VISALGORITHM_NAMESPACE_END