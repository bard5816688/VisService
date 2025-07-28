#include "ShapeMatching.h"

VISSERVICE_NAMESPACE_BEGIN

ShapeMatching::ShapeMatching(std::string moduleName)
{
	setName(moduleName);
}

CStatus ShapeMatching::init()
{
	CStatus status;
	//shapeMatchingParams_.readDb(taskName_);

	status = CGRAPH_CREATE_GPARAM(GParam<VisAlgorithm::Region>, getName() + "." + "findRegion_");
	status = CGRAPH_CREATE_GPARAM(GParam<QPointF>, getName() + "." + "findPosition_");
	status = CGRAPH_CREATE_GPARAM(GParam<double>, getName() + "." + "findAngle_");
	status = CGRAPH_CREATE_GPARAM(GParam<double>, getName() + "." + "findScore_");

	CGraph::CGRAPH_ECHO("ShapeMatchingNode::init()");
	return status;
}

CStatus ShapeMatching::run()
{
	CStatus status;
	auto roi = CGRAPH_GET_GPARAM(GParam<VisAlgorithm::Region>, "");
	roi->value_;

	CGraph::CGRAPH_ECHO("ShapeMatchingNode::run()");
	return CStatus();
}

std::vector<std::string> ShapeMatching::GetOutputParamNames()
{
	return ReflectStruct<ShapeMatching>::getMemberNames();
}

VISSERVICE_NAMESPACE_END