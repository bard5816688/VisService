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
	//���ݿ��м���ģ�����ɲ���
	//shapeMatchingParams_.readDb(taskName_);

	//����ģ���������
	status = CGRAPH_CREATE_GPARAM(ShapeMatchingOutputParams, "ShapeMatchingOutputParams");

	//����
	CGraph::CGRAPH_ECHO("ShapeMatchingNode::init()");
	return status;
}

CStatus ShapeMatching::run()
{
	CStatus status;
	//��ȡ�ڵ���������(����ʱ��ȡ)
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