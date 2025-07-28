#include "ShapeMatching.h"

VISSERVICE_NAMESPACE_BEGIN

ShapeMatching::ShapeMatching()
{
	setName("ShapeMatching");
}

CStatus ShapeMatching::init()
{
	CStatus status;
	//读取（db）模块自身参数
	//shapeMatchingParams_.readDb(taskName_);
	shapeMatchingParams_.runParams_.row = &(findPositionRow_.value_);
	shapeMatchingParams_.runParams_.column = &(findPositionCol_.value_);
	shapeMatchingParams_.runParams_.angle = &(findAngle_.value_);
	shapeMatchingParams_.runParams_.score = &(findScore_.value_);

	//创建模块输出参数
	status = CREATE_GPARAM(GParam<VisAlgorithm::Region>, ShapeMatching.findRegion_);
	status = CREATE_GPARAM(GParam<QPointF>, ShapeMatching.findPosition_);
	status = CREATE_GPARAM(GParam<double>, ShapeMatching.findAngle_);
	status = CREATE_GPARAM(GParam<double>, ShapeMatching.findScore_);

	return status;
}

CStatus ShapeMatching::run()
{
	CStatus status;
	FillinInputParams();
	shapeMatchingParams_.shapeModel_.FindShapeModel(shapeMatchingParams_.runParams_);
	return status;
}

std::vector<std::string> ShapeMatching::GetOutputParamNames()
{
	return ReflectStruct<ShapeMatching>::getMemberNames();
}

ReturnVoid ShapeMatching::FillinInputParams()
{
	auto srcImg = CGRAPH_GET_GPARAM(GParam<VisAlgorithm::Image>, shapeMatchingParams_.sourceImage_.first);
	shapeMatchingParams_.sourceImage_.second = srcImg->value_;
	auto roi = CGRAPH_GET_GPARAM(GParam<VisAlgorithm::Region>, shapeMatchingParams_.roi_.first);
	shapeMatchingParams_.roi_.second = roi->value_;
	return ReturnVoid();
}

VISSERVICE_NAMESPACE_END