#pragma once
#include "DispenseTrajectoryPlannerParams.h"

VISSERVICE_NAMESPACE_BEGIN

class VISSERVICE_EXPORT DispenseTrajectoryPlanner
{
public:
	DispenseTrajectoryPlanner();
	Return<std::vector<QPointF>> CalculateTrajectory(std::shared_ptr<CalculateTrajectoryParams> params);
	Return<std::vector<QPointF>> TransformWorkCoord2ImageCoord(std::shared_ptr<TransformWorkCoord2ImageCoordParams> params);
	Return<std::vector<QPointF>> Transform2TemplateCoord(const Transform2TemplateCoordParams& params);
};

VISSERVICE_NAMESPACE_END