#include "ShapeMatching.h"

VISSERVICE_NAMESPACE_BEGIN

ShapeMatching::ShapeMatching(std::string name)
{

}

void ShapeMatching::SetInputParam(const std::string& key, const QVariant& value)
{

}

QVariant ShapeMatching::GetOutParam(const std::string& key)
{

}

CStatus ShapeMatching::init()
{
	CStatus status;
	//数据库中加载模块自由参数
	//shapeMatchingParams_.readDb(taskName_);

	//创建模块输出参数
	status = CGRAPH_CREATE_GPARAM(ShapeMatchingOutputParams, "ShapeMatchingOutputParams");

	//其他
	CGraph::CGRAPH_ECHO("ShapeMatchingNode::init()");
	return status;
}

CStatus ShapeMatching::run()
{
	CStatus status;
	//获取节点的输入参数(运行时获取)
	auto path = splitInputParamsPath(shapeMatchingInputParams_.sourceImage_.first);


	auto sourceImage = CGRAPH_GET_GPARAM()
		auto sourceImage = this->template getGParam<VisAlgorithm::Image>();;
	{
		CGRAPH_PARAM_READ_CODE_BLOCK();
		shapeMatchingInputParams_.sourceImage_;
	}

	CGraph::CGRAPH_ECHO("ShapeMatchingNode::run()");
	return CStatus();
}

VISSERVICE_NAMESPACE_END