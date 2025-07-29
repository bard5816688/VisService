#include "ShapeMatchingParams.h"

template<>
QString ParamTraits<VisService::ShapeMatchingParams>::TableName()
{

}

template<>
QJsonObject ParamTraits<VisService::ShapeMatchingParams>::ToJson(const VisService::ShapeMatchingParams& param)
{

}

template<>
bool ParamTraits<VisService::ShapeMatchingParams>::FromJson(const QJsonObject& json, VisService::ShapeMatchingParams& param)
{

}


VISSERVICE_NAMESPACE_BEGIN

ParamManager<ShapeMatchingParams>& GlobalShapeMatchingParams()
{
	static ParamManager<ShapeMatchingParams> instance(ParamStorage<ShapeMatchingParams>("shape.db"));
	return instance;
}

VISSERVICE_NAMESPACE_END