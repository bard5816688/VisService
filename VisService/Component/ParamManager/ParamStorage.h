#pragma once
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QDebug>
#include <optional>
#include <mutex>
#include <map>
#include <string>
#include "ParamTraits.h"// 必须为每种 T 提供 ParamTraits<T>::ToJson / FromJson / TableName

class DbConnectionManager
{
public:
	static QSqlDatabase instance(const QString& dbPath)
	{
		static std::mutex mutex;
		static std::map<QString, QSqlDatabase> dbMap;

		std::lock_guard<std::mutex> lock(mutex);
		auto it = dbMap.find(dbPath);
		if (it != dbMap.end())
			return it->second;

		QString connName = QString("shared_conn_%1").arg(dbPath);
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connName);
		db.setDatabaseName(dbPath);
		if (!db.open())
		{
			qWarning() << "Failed to open database:" << db.lastError().text();
		}
		dbMap[dbPath] = db;
		return dbMap[dbPath];
	}
};

template <typename ParamType>
class ParamStorage
{
public:
	explicit ParamStorage(const QString& dbPath)
		: dbPath_(dbPath), db_(DbConnectionManager::instance(dbPath)), tableName_(ParamTraits<ParamType>::TableName())
	{
		EnsureTable();
	}

	std::optional<ParamType> Load(const std::string& key)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		auto jsonStrOpt = LoadDb(QString::fromStdString(key));
		if (!jsonStrOpt.has_value())
			return std::nullopt;

		const QJsonDocument doc = QJsonDocument::fromJson(jsonStrOpt->toUtf8());
		if (doc.isNull() || !doc.isObject()) {
			qWarning() << "Load failed: invalid JSON for key:" << QString::fromStdString(key);
			return std::nullopt;
		}

		ParamType value;
		if (!ParamTraits<ParamType>::FromJson(doc.object(), value)) {
			qWarning() << "Load failed: JSON deserialization failed for key:" << QString::fromStdString(key);
			return std::nullopt;
		}

		return value;
	}

	bool Save(const std::string& key, const ParamType& value)
	{
		QJsonObject json = ParamTraits<ParamType>::ToJson(value);
		const QJsonDocument doc(json);
		return InsertDb(QString::fromStdString(key), QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
	}

	bool Update(const std::string& key, const ParamType& value)
	{
		QJsonObject json = ParamTraits<ParamType>::ToJson(value);
		const QJsonDocument doc(json);
		return UpdateDb(QString::fromStdString(key), QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
	}

	bool Remove(const std::string& key)
	{
		return RemoveDb(QString::fromStdString(key));
	}

private:
	void EnsureTable()
	{
		QSqlQuery query(db_);
		const QString sql = QString(
			"CREATE TABLE IF NOT EXISTS %1 ("
			"key TEXT PRIMARY KEY, "
			"value TEXT NOT NULL)")
			.arg(tableName_);
		if (!query.exec(sql))
		{
			qWarning() << "Failed to create table" << tableName_ << ":" << query.lastError().text();
		}
	}

	std::optional<QString> LoadDb(const QString& key)
	{
		QSqlQuery query(db_);
		query.prepare(QString("SELECT value FROM %1 WHERE key = :key").arg(tableName_));
		query.bindValue(":key", key);
		if (!query.exec())
		{
			qWarning() << "LoadDb failed to execute query:" << query.lastError().text();
			return std::nullopt;
		}
		if (!query.next())
			return std::nullopt; // Not found
		return query.value(0).toString();
	}

	bool InsertDb(const QString& key, const QString& jsonStr)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		QSqlQuery query(db_);
		query.prepare(QString("INSERT INTO %1 (key, value) VALUES (:key, :value)").arg(tableName_));
		query.bindValue(":key", key);
		query.bindValue(":value", jsonStr);
		return query.exec();
	}

	bool UpdateDb(const QString& key, const QString& jsonStr)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		QSqlQuery query(db_);
		query.prepare(QString("UPDATE %1 SET value = :value WHERE key = :key").arg(tableName_));
		query.bindValue(":value", jsonStr);
		query.bindValue(":key", key);
		return query.exec();
	}

	bool RemoveDb(const QString& key)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		QSqlQuery query(db_);
		query.prepare(QString("DELETE FROM %1 WHERE key = :key").arg(tableName_));
		query.bindValue(":key", key);
		return query.exec();
	}

private:
	QString dbPath_;
	QSqlDatabase db_;
	QString tableName_;
	std::mutex mutex_;

};
