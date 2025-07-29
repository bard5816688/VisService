#pragma once
#include <QJsonObject>
#include <QString>

template<typename ParamType>
struct ParamTraits 
{
    static QString TableName();
    static QJsonObject ToJson(const ParamType& param);
    static bool FromJson(const QJsonObject& json, ParamType& param);
};