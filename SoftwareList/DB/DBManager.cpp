// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "DBManager.h"

#include <QDebug>

DBManager::DBManager(QObject* parent)
	: QObject(parent)
{
	QString driverName("QSQLITE");

	if (!QSqlDatabase::drivers().contains(driverName)) {
		qCritical() << "No SQLite driver found";
		exit(-1);
	}

	QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
	db.setDatabaseName(":memory:");

	if (!db.open()) {
		qCritical() << "Database opening failed: " << db.lastError().text();
		exit(-1);
	}

	QSqlError err = createTables();
	if (err.type() != QSqlError::NoError) {
		qCritical() << "Create Table error: " << err.text();
		return;
	}

	err = prepareStatements(db);
	if (err.type() != QSqlError::NoError) {
		qCritical() << "Prepare statements error: " << err.text();
		return;
	}

	populateDB();
}

QVariant DBManager::addCategory(QString name)
{
	insertCategoryQuery.addBindValue(name);
	insertCategoryQuery.exec();
	return insertCategoryQuery.lastInsertId();
}

QVariant DBManager::addPlatform(QString name)
{
	insertPlatformQuery.addBindValue(name);
	insertPlatformQuery.exec();
	return insertPlatformQuery.lastInsertId();
}

QVariant DBManager::addRole(QString name, QString description)
{
	insertRoleQuery.addBindValue(name);
	insertRoleQuery.addBindValue(description);
	insertRoleQuery.exec();
	return insertRoleQuery.lastInsertId();
}

QStringList DBManager::getCategoryList()
{
	QStringList categories;

	QLatin1String queryStr(R"(
		SELECT NAME
		FROM CATEGORY
		ORDER BY NAME
	)");
	QSqlQuery q(queryStr);
	while (q.next()) {
		QString name = q.value(0).toString();
		categories << name;
	}
	return categories;
}

QStringList DBManager::getPlatformList()
{
	QStringList platforms;

	QLatin1String queryStr(R"(
		SELECT NAME
		FROM PLATFORM
		ORDER BY ID
	)");
	QSqlQuery q(queryStr);
	while (q.next()) {
		QString name = q.value(0).toString();
		platforms << name;
	}
	return platforms;
}

QSqlError DBManager::createTables()
{
	QSqlQuery q;
	const QStringList tableCreationQueries({ SOFTWARE_TABLE_SQL,
		CATEGORY_TABLE_SQL,
		PLATFORM_TABLE_SQL,
		PREFERENCE_ROLE_TABLE_SQL,
		REQUIREMENT_TABLE_SQL,
		SOFTWARE_CATEGORY_TABLE_SQL,
		SOFTWARE_PLATFORM_TABLE_SQL,
		SOFTWARE_REQUIREMENT_TABLE_SQL,
		CAT_PLAT_SOFT_ROLE_TABLE_SQL });

	for (const auto& queryStr : tableCreationQueries) {
		if (!q.exec(queryStr)) {
			return q.lastError();
		}
	}

	return QSqlError();
}

QSqlError DBManager::prepareStatements(QSqlDatabase& db)
{
	// QSqlQuery must be created after database connection is established.
	insertSoftwareQuery = QSqlQuery(db);
	insertCategoryQuery = QSqlQuery(db);
	insertPlatformQuery = QSqlQuery(db);
	insertRoleQuery = QSqlQuery(db);
	insertRequirementQuery = QSqlQuery(db);
	insertSoftwareCategoryQuery = QSqlQuery(db);
	insertSoftwarePlatformQuery = QSqlQuery(db);
	insertSoftwareRequirementQuery = QSqlQuery(db);
	insertCatPlatSoftRoleQuery = QSqlQuery(db);

	using namespace std;
	const QVector<std::pair<QSqlQuery*, QLatin1String>> insertQueryPairList({ pair<QSqlQuery*, QLatin1String>(&insertSoftwareQuery, INSERT_SOFTWARE_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertCategoryQuery, INSERT_CATEGORY_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertPlatformQuery, INSERT_PLATFORM_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertRoleQuery, INSERT_ROLE_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertRequirementQuery, INSERT_REQUIREMENT_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwareCategoryQuery, INSERT_SOFTWARE_CATEGORY_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwarePlatformQuery, INSERT_SOFTWARE_PLATFORM_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwareRequirementQuery, INSERT_SOFTWARE_REQUIREMENT_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertCatPlatSoftRoleQuery, INSERT_CAT_PLAT_SOFT_ROLE_SQL) });

	for (const auto& insQryPair : insertQueryPairList) {
		QSqlQuery* q = insQryPair.first;
		const QLatin1String& qStr = insQryPair.second;
		if (!q->prepare(qStr)) {
			return q->lastError();
		}
	}

	return QSqlError();
}

void DBManager::populateDB()
{
	// Check Platform
	QLatin1String countPlatformSql(R"(
		SELECT COUNT(*)
		FROM PLATFORM
	)");
	QSqlQuery countPlatformQuery(countPlatformSql);
	if (countPlatformQuery.next()) {
		int platformCount = countPlatformQuery.value(0).toInt();
		if (platformCount > 0) {
			return; // DB already has platform(s), no need to populate
		}

		addPlatform("Windows");
		addPlatform("macOS");
		addPlatform("Linux");
		addPlatform("android");
		addPlatform("iOS");
	}

	// Check Role
	QLatin1String countRoleSql(R"(
		SELECT COUNT(*)
		FROM PREFERENCE_ROLE
	)");
	QSqlQuery countRoleQuery(countRoleSql);
	if (countRoleQuery.next()) {
		int roleCount = countRoleQuery.value(0).toInt();
		if (roleCount > 0) {
			return; // DB already has role(s), no need to populate
		}

		addRole("Main", "Fulfills the need.");
		addRole("Fallback", "Backup. Not necessarily a drop in replacement.");
		addRole("Primary", "Meets most requirements, but cannot fulfill all requirements. Needs other to make up the missing parts");
		addRole("Secondary", "Augments Primary towards fulfilling requirements.");
		addRole("Tertiary", "Augments Primary & Secondary towards fulfilling requirements.");
		addRole("Quaternary", "Augments Primary, Secondary & Tertiary towards fulfilling requirements. "
							  "If you need this level, your category might be too broad. Consider breaking it up.");
	}
}

QVariant DBManager::addRequirement(QString req, int categoryID)
{
	insertRequirementQuery.addBindValue(req);
	insertRequirementQuery.addBindValue(categoryID);
	insertRequirementQuery.exec();
	return insertRequirementQuery.lastInsertId();
}
