#pragma once

#include "VisAlgorithmDefs.h"
#include "HShapeModelStrategy.h"
#include "VisShapeModelStrategy.h"

VISALGORITHM_NAMESPACE_BEGIN



template<typename Strategy>
class ShapeModel 
{
public:
	void CreateShapeModel(const Image& templateImg, int64_t numLevels, double angleStart, double angleExtent, double angleStep, const char* optimization, const char* metric, int64_t contrast, int64_t minContrast);
	void ReadShapeModel(const char* fileName);
	void FindShapeModel(const Image& image, double angleStart, double angleExtent, double minScore, int64_t numMatches, double maxOverlap, const char* subPixel, int64_t numLevels, double greediness, Tuple* row, Tuple* column, Tuple* angle, Tuple* score) const;
	void WriteShapeModel(const char* fileName) const;
	void ClearShapeModel() const;

private:
    Strategy strategy_;
};

VISALGORITHM_NAMESPACE_END

#include "ShapeMode.inl"
