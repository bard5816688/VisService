#pragma once
#include "ParamTraits.h"
// ParamTraits<ParamType> 需自行实现，提供:
// static QString TableName();
// static QJsonObject ToJson(const ParamType&);
// static bool FromJson(const QJsonObject&, ParamType&);

template<typename ParamType>
ParamStorage<ParamType>& ParamStorage<ParamType>::Instance(const QString& dbPath) 
{
    static ParamStorage<ParamType> instance(dbPath);
    return instance;
}

template<typename ParamType>
ParamStorage<ParamType>::ParamStorage(const QString& dbPath) 
{
    const QString tableName = ParamTraits<ParamType>::TableName();
    worker_ = new DbWorker(dbPath, tableName);
    thread_ = new QThread();
    worker_->moveToThread(thread_);
    thread_->start();
}

template<typename ParamType>
ParamStorage<ParamType>::~ParamStorage() 
{
    thread_->quit();
    thread_->wait();
    delete worker_;
    delete thread_;
}

template<typename ParamType>
std::optional<ParamType> ParamStorage<ParamType>::Load(const std::string& key) {
    QString json;
    int res = 0;
    QMetaObject::invokeMethod(worker_, "Load", Qt::BlockingQueuedConnection,
        Q_RETURN_ARG(int, res),
        Q_ARG(QString, QString::fromStdString(key)),
        Q_ARG(QString&, json));
    if (res != 0) return std::nullopt;

    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (!doc.isObject()) return std::nullopt;

    ParamType value;
    if (!ParamTraits<ParamType>::FromJson(doc.object(), value))
        return std::nullopt;

    return value;
}

template<typename ParamType>
bool ParamStorage<ParamType>::Save(const std::string& key, const ParamType& value) 
{
    QJsonDocument doc(ParamTraits<ParamType>::ToJson(value));
    bool ok = false;
    QMetaObject::invokeMethod(worker_, "Save", Qt::BlockingQueuedConnection,
        Q_RETURN_ARG(bool, ok),
        Q_ARG(QString, QString::fromStdString(key)),
        Q_ARG(QString, QString::fromUtf8(doc.toJson(QJsonDocument::Compact))));
    return ok;
}

template<typename ParamType>
bool ParamStorage<ParamType>::Update(const std::string& key, const ParamType& value) 
{
    QJsonDocument doc(ParamTraits<ParamType>::ToJson(value));
    bool ok = false;
    QMetaObject::invokeMethod(worker_, "Update", Qt::BlockingQueuedConnection,
        Q_RETURN_ARG(bool, ok),
        Q_ARG(QString, QString::fromStdString(key)),
        Q_ARG(QString, QString::fromUtf8(doc.toJson(QJsonDocument::Compact))));
    return ok;
}

template<typename ParamType>
bool ParamStorage<ParamType>::Remove(const std::string& key) 
{
    bool ok = false;
    QMetaObject::invokeMethod(worker_, "Remove", Qt::BlockingQueuedConnection,
        Q_RETURN_ARG(bool, ok),
        Q_ARG(QString, QString::fromStdString(key)));
    return ok;
}
