#pragma once
#include "../ModuleObject.h"
#include "VisAlgorithm.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

struct ShapeMatchingParams
{
	std::string keyName_;
	VisAlgorithm::Image refImage_;
	VisAlgorithm::CreateShapeModelParams modelParams_;
	VisAlgorithm::ShapeModel shapeModel_;
	VisAlgorithm::FindShapeModelParams runParams_;
};

struct ShapeMatchingInputParams
{
	ModuleInputParamsMember<VisAlgorithm::Image> sourceImage_;
	ModuleInputParamsMember<VisAlgorithm::Region> roi_;

};

struct ShapeMatchingOutputParams
{
	VisAlgorithm::Region findRegion_;
	QPointF findPosition_;
	double findAngle_;
	double findScore_;
};


class ShapeMatching : public BaseModule
{
public:
	ShapeMatching(std::string name);

	virtual void SetInputParam(const std::string& key, const QVariant& value)override;
	virtual QVariant GetOutParam(const std::string& key)override;
	virtual CStatus init() override;
	virtual CStatus run() override;

private:
	ShapeMatchingParams shapeMatchingParams_;
	ShapeMatchingInputParams shapeMatchingInputParams_;
	ShapeMatchingOutputParams shapeMatchingOutputParams_;

};

VISSERVICE_NAMESPACE_END