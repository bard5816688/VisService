#pragma once
#include "../Basic/BasicReturn.h"
#include "../Tuple/Tuple.h"
#include "../Region/Region.h"
#include "../Contour/Contour.h"
#include "../Image/Image.h"

VISALGORITHM_NAMESPACE_BEGIN

struct CreateShapeModelParams
{
	const Image& templateImg_;
	int64_t numLevels_;
	double angleStart_;
	double angleExtent_;
	double angleStep_;
	const char* optimization_;
	const char* metric_;
	int64_t contrast_;
	int64_t minContrast_;
};

template<typename T>
concept IsShapeModelStrategy = RuleOfFive<T> && requires(
	T t,
	const char* constCharPtr,
	CreateShapeModelParams  createModelParams
	)
{
	{ t.ReadShapeModel(constCharPtr) } -> std::same_as<ResultVoid>;
	{ t.CreateShapeModel(createModelParams) } -> std::same_as<ResultVoid>;
};


VISALGORITHM_NAMESPACE_END