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
	ShapeMatching();
	virtual CStatus init() override;
	virtual CStatus run() override;
	virtual std::vector<std::string> GetOutputParamNames() override;

private:
	ReturnVoid FillinInputParams();

private:
	ShapeMatchingParams shapeMatchingParams_;
	GParam<VisAlgorithm::Region> findRegion_;
	GParam<VisAlgorithm::Tuple> findPositionRow_;
	GParam<VisAlgorithm::Tuple> findPositionCol_;
	GParam<VisAlgorithm::Tuple> findAngle_;
	GParam<VisAlgorithm::Tuple> findScore_;

	friend struct Reflectable<ShapeMatching>;
};

REFLECT_STRUCT(ShapeMatching,
	MEMBER(ShapeMatching, findRegion_),
	MEMBER(ShapeMatching, findPositionRow_),
	MEMBER(ShapeMatching, findPositionCol_),
	MEMBER(ShapeMatching, findAngle_),
	MEMBER(ShapeMatching, findScore_)
)


VISSERVICE_NAMESPACE_END