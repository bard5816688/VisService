#include "DbWorker.h"

DbWorker::DbWorker(const QString& dbPath, const QString& tableName, QObject* parent)
    : QObject(parent), dbPath_(dbPath), tableName_(tableName)
{
}

int DbWorker::Load(const QString& key, QString& jsonStr)
{
    EnsureInitialized();
    if (!initialized_)
        return -1;

    QSqlQuery query(db_);
    query.prepare(QString("SELECT value FROM %1 WHERE key = :key").arg(tableName_));
    query.bindValue(":key", key);
    if (!query.exec() || !query.next())
        return -2;

    jsonStr = query.value(0).toString();
    return 0;
}

bool DbWorker::Save(const QString& key, const QString& jsonStr)
{
    EnsureInitialized();
    if (!initialized_)
        return false;

    QSqlQuery query(db_);
    query.prepare(QString("INSERT OR REPLACE INTO %1 (key, value) VALUES (:key, :value)").arg(tableName_));
    query.bindValue(":key", key);
    query.bindValue(":value", jsonStr);
    return query.exec();
}

bool DbWorker::Update(const QString& key, const QString& jsonStr)
{
    EnsureInitialized();
    if (!initialized_)
        return false;

    // 可选：检查 key 是否存在（可省略以提高性能）
    QSqlQuery checkQuery(db_);
    checkQuery.prepare(QString("SELECT 1 FROM %1 WHERE key = :key").arg(tableName_));
    checkQuery.bindValue(":key", key);
    if (!checkQuery.exec() || !checkQuery.next())
        return false;  // key 不存在，不能 update

    QSqlQuery query(db_);
    query.prepare(QString("UPDATE %1 SET value = :value WHERE key = :key").arg(tableName_));
    query.bindValue(":key", key);
    query.bindValue(":value", jsonStr);
    return query.exec();
}


bool DbWorker::Remove(const QString& key)
{
    EnsureInitialized();
    if (!initialized_)
        return false;

    QSqlQuery query(db_);
    query.prepare(QString("DELETE FROM %1 WHERE key = :key").arg(tableName_));
    query.bindValue(":key", key);
    return query.exec();
}


void DbWorker::EnsureInitialized()
{
    if (initialized_)
        return;

    const QString connName = QString("conn_%1").arg(reinterpret_cast<quintptr>(this));
    db_ = QSqlDatabase::addDatabase("QSQLITE", connName);
    db_.setDatabaseName(dbPath_);
    if (!db_.open()) {
        qWarning() << "Failed to open database:" << db_.lastError().text();
        return;
    }

    QSqlQuery query(db_);
    const QString createSql = QString("CREATE TABLE IF NOT EXISTS %1 (key TEXT PRIMARY KEY, value TEXT NOT NULL)")
        .arg(tableName_);
    if (!query.exec(createSql)) {
        qWarning() << "Failed to create table:" << query.lastError().text();
        return;
    }

    initialized_ = true;
}
