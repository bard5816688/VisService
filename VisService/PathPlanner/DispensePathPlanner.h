#pragma once
#include "DispensePathPlannerParams.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT DispensePathPlanner
{
public:
	DispensePathPlanner();
	Return<std::vector<QPointF>> PlanDispensePath(std::shared_ptr<PlanDispensePathParams> params);
	Return<std::vector<QPointF>> TransformWorkCoord2ImageCoord(std::shared_ptr<TransformWorkCoord2ImageCoordParams> params);
	Return<std::vector<QPointF>> Transform2TemplateCoord(const Transform2TemplateCoordParams& params);
};

VISSERVICE_NAMESPACE_END