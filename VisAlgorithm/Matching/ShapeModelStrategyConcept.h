#pragma once
#include "BasicDefs.h"
#include "BasicReturn.h"
#include "Tuple.h"
#include "Region.h"
#include "Image.h"

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
concept IsShapeModelStrategy = requires(
    T                       t, 
    const char*             fileName, 
    CreateShapeModelParams  cp
    )
{
	{ t.ReadShapeModel(fileName) }  -> std::same_as<ResultVoid>;
	{ t.CreateShapeModel(cp) }      -> std::same_as<ResultVoid>;
};


VISALGORITHM_NAMESPACE_END