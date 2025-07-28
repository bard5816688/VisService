#include "DispensePathPlanner.h"

VISSERVICE_NAMESPACE_BEGIN

DispensePathPlanner::DispensePathPlanner()
{

}

Return<std::vector<QPointF>> DispensePathPlanner::PlanDispensePath(const PlanDispensePathParams& params)
{
	return Return<std::vector<QPointF>>();
}

Return<std::vector<QPointF>> DispensePathPlanner::TransformWorkCoord2ImageCoord(const TransformWorkCoord2ImageCoordParams& params)
{
	return Return<std::vector<QPointF>>();
}

Return<std::vector<QPointF>> DispensePathPlanner::Transform2TemplateCoord(const Transform2TemplateCoordParams& params)
{
	return Return<std::vector<QPointF>>();
}

VISSERVICE_NAMESPACE_END