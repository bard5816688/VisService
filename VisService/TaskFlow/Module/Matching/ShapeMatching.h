#pragma once
#include "../ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

struct ShapeMatchingParams
{
	std::string taskName_;
	ModuleInputParamPath<VisAlgorithm::Image> sourceImage_;
	ModuleInputParamPath<VisAlgorithm::Region> roi_;
	VisAlgorithm::Image refImage_;
	VisAlgorithm::CreateShapeModelParams modelParams_;
	VisAlgorithm::ShapeModel shapeModel_;
	VisAlgorithm::FindShapeModelParams runParams_;
};

class ShapeMatching : public ModuleBase
{
public:
	ShapeMatching(std::string moduleName);
	virtual CStatus init() override;
	virtual CStatus run() override;
	virtual std::vector<std::string> GetOutputParamNames() override;

private:
	ShapeMatchingParams shapeMatchingParams_;
	GParam<VisAlgorithm::Region> findRegion_;
	GParam<QPointF> findPosition_;
	GParam<double> findAngle_;
	GParam<double> findScore_;

	friend struct Reflectable<ShapeMatching>;
};

REFLECT_STRUCT(ShapeMatching,
	MEMBER(ShapeMatching, findRegion_),
	MEMBER(ShapeMatching, findPosition_),
	MEMBER(ShapeMatching, findAngle_),
	MEMBER(ShapeMatching, findScore_)
)


VISSERVICE_NAMESPACE_END