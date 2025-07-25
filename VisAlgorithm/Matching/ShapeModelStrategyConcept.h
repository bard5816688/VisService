#pragma once
#include "../Basic/BasicReturn.h"
#include "../Tuple/Tuple.h"
#include "../Region/Region.h"
#include "../Contour/Contour.h"
#include "../Image/Image.h"

VISALGORITHM_NAMESPACE_BEGIN

struct CreateShapeModelParams
{
	Image templateImg_;
	int64_t numLevels_;
	double angleStart_;
	double angleExtent_;
	double angleStep_;
	std::string optimization_;
	std::string metric_;
	int64_t contrast_;
	int64_t minContrast_;
};

struct FindShapeModelParams
{
	Image searchImage;
	double angleStart;
	double angleExtent;
	double minScore;
	int64_t numMatches;
	double maxOverlap;
	std::string subPixel;
	int64_t numLevels;
	double greediness;
	Tuple* row;
	Tuple* column;
	Tuple* angle;
	Tuple* score;
};

struct ShapeModelParams
{
	double* angleStart;
	double* angleExtent;
	double* angleStep;
	double* scaleMin;
	double* scaleMax;
	double* scaleStep;
	std::string* metric;
	int64_t* minContrast;
};


template<typename T>
concept IsShapeModelStrategy = RuleOfFive<T> && requires(
	T t,
	const T& ct,
	const char* constCharPtr,
	CreateShapeModelParams  createModelParams,
	const FindShapeModelParams  findModelParams,
	const ShapeModelParams shapeModelParams
	)
{
	{ t.ReadShapeModel(constCharPtr) } -> std::same_as<ResultVoid>;
	{ t.CreateShapeModel(createModelParams) } -> std::same_as<ResultVoid>;
	{ ct.FindShapeModel(findModelParams) } -> std::same_as<ResultVoid>;
	{ ct.GetShapeModelParams(shapeModelParams) } -> std::same_as<Result<int64_t>>;
};

VISALGORITHM_NAMESPACE_END