#include "ShapeMatchingParams.h"

template<>
QString ParamTraits<VisService::ShapeMatchingParams>::TableName()
{
	return "";
}

template<>
QJsonObject ParamTraits<VisService::ShapeMatchingParams>::ToJson(const VisService::ShapeMatchingParams& param)
{
	return QJsonObject();
}

template<>
bool ParamTraits<VisService::ShapeMatchingParams>::FromJson(const QJsonObject& json, VisService::ShapeMatchingParams& param)
{
	return true;
}


VISSERVICE_NAMESPACE_BEGIN

ParamManager<ShapeMatchingParams>& GlobalShapeMatchingParams()
{
	static ParamManager<ShapeMatchingParams> instance("shape.db");
	return instance;
}

VISSERVICE_NAMESPACE_END