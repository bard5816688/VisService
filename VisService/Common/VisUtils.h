#pragma once
#include "../Basic/BasicObject.h"
#include "VisAlgorithm.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT VisUtils
{
	static ReturnVoid convertImage2Gray(QImage& dst, const QImage& src);
	static ReturnVoid convertImage2QImage(QImage& dst, const VisAlgorithm::Image& src);
};

VISSERVICE_EXPORT ReturnVoid InitVisService(const VisInitParams& params);
VISSERVICE_EXPORT ReturnVoid SetOperationMode(VisOperationMode mode);
VISSERVICE_EXPORT Return<QPointF> GetPixelResolution(WorkStation station);

VISSERVICE_NAMESPACE_END