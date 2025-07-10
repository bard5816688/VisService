#pragma once

#include "ShapeModel.h"

VISALGORITHM_NAMESPACE_BEGIN

template<typename Strategy>
void ShapeModel<Strategy>::CreateShapeModel(const Image& templateImg, int64_t numLevels, double angleStart, double angleExtent, double angleStep, const char* optimization, const char* metric, int64_t contrast, int64_t minContrast)
{
	strategy_.CreateShapeModel(templateImg.GetHImage(), numLevels, angleStart, angleExtent, angleStep, optimization, metric, contrast, minContrast);
}

template<typename Strategy>
inline void ShapeModel<Strategy>::ReadShapeModel(const char* fileName)
{
}

template<typename Strategy>
inline void ShapeModel<Strategy>::FindShapeModel(const Image& image, const Region& rgn, double angleStart, double angleExtent, double minScore, int64_t numMatches, double maxOverlap, const char* subPixel, int64_t numLevels, double greediness, Tuple* row, Tuple* column, Tuple* angle, Tuple* score) const
{
}

template<typename Strategy>
inline void ShapeModel<Strategy>::WriteShapeModel(const char* fileName) const
{
}

template<typename Strategy>
inline void ShapeModel<Strategy>::ClearShapeModel() const
{
}


VISALGORITHM_NAMESPACE_END