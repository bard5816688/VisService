#pragma once

#include "VisAlgorithmDefs.h"

VISALGORITHM_NAMESPACE_BEGIN

enum class PixelFormat
{
	Mono8,     ///< 8λ�Ҷ�ͼ��
	Mono10,    ///< 10λ�Ҷ�ͼ��
	Mono12,    ///< 12λ�Ҷ�ͼ��
	Mono16,    ///< 16λ�Ҷ�ͼ��
	Rgb8,      ///< 24λRGB��ɫͼ��
	Bgr8,      ///< 24λBGR��ɫͼ��
	Rgba8,     ///< 32λRGBA��ɫͼ��
	Bgra8,     ///< 32λBGRA��ɫͼ��
	BayerRg8,  ///< 8λBayer RG��ʽ
	BayerGb8,  ///< 8λBayer GB��ʽ
	BayerGr8,  ///< 8λBayer GR��ʽ
	BayerBg8,  ///< 8λBayer BG��ʽ
	Unknown    ///< δ֪��ʽ
};

class VisImage
{
public:
	VisImage();
	VisImage(uint32_t width, uint32_t height, PixelFormat format);
	~VisImage();

	static int GetBytesPerPixel(PixelFormat format);

protected:
	uint32_t width_;                                  ///< ͼ����
	uint32_t height_;                                 ///< ͼ��߶�
	PixelFormat pixelFormat_;                         ///< ���ظ�ʽ
	std::shared_ptr<uint8_t> data_;                   ///< ͼ������
	size_t dataSize_;                                 ///< ���ݴ�С
	uint64_t frameId_;                                ///< ֡ID
	std::chrono::system_clock::time_point timestamp_; ///< ʱ���
	std::string cameraSerialNumber_;                  ///< ������к�
};

VISALGORITHM_NAMESPACE_END