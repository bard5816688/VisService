#pragma once
#include <QObject>
#include <QThread>
#include <QMetaObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <optional>
#include "DbWorker.h"

template<typename ParamType>
class ParamStorage 
{
public:
    static ParamStorage& Instance(const QString& dbPath);

    std::optional<ParamType> Load(const std::string& key);
    bool Save(const std::string& key, const ParamType& value);
    bool Update(const std::string& key, const ParamType& value);
    bool Remove(const std::string& key);

private:
    ParamStorage(const QString& dbPath);
    ~ParamStorage();

    QThread* thread_;
    DbWorker* worker_;
};

#include "ParamStorage.inl"
