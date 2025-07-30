#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DbWorker : public QObject 
{
    Q_OBJECT
public:
    explicit DbWorker(const QString& dbPath, const QString& tableName, QObject* parent = nullptr);

public slots:
    int Load(const QString& key, QString& json);
    bool Save(const QString& key, const QString& json);
    bool Update(const QString& key, const QString& json);
    bool Remove(const QString& key);

private:
    void EnsureInitialized();

private:
    QString dbPath_;
    QString tableName_;
    QSqlDatabase db_;
    bool initialized_ = false;
};