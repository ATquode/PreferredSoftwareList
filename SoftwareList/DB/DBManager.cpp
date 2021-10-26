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

QVariant DBManager::addRequirement(QString req, int categoryID)
{
	insertRequirementQuery.addBindValue(req);
	insertRequirementQuery.addBindValue(categoryID);
	insertRequirementQuery.exec();
	return insertRequirementQuery.lastInsertId();
}

QVariant DBManager::addPlatform(QString name)
{
	insertPlatformQuery.addBindValue(name);
	insertPlatformQuery.exec();
	return insertPlatformQuery.lastInsertId();
}

QVariant DBManager::addRole(QString name, QString description, int level)
{
	insertRoleQuery.addBindValue(name);
	insertRoleQuery.addBindValue(description);
	insertRoleQuery.addBindValue(level);
	insertRoleQuery.exec();
	return insertRoleQuery.lastInsertId();
}

QVariant DBManager::addSoftwareItem(const SoftwareItem& item)
{
	insertSoftwareQuery.addBindValue(item.name);
	insertSoftwareQuery.addBindValue(item.limitation);
	insertSoftwareQuery.addBindValue(item.url);
	insertSoftwareQuery.addBindValue(item.notes);
	insertSoftwareQuery.exec();
	return insertSoftwareQuery.lastInsertId();
}

QVariant DBManager::addSoftwareCategoryLink(int softID, int catID)
{
	insertSoftwareCategoryQuery.addBindValue(softID);
	insertSoftwareCategoryQuery.addBindValue(catID);
	insertSoftwareCategoryQuery.exec();
	return insertSoftwareCategoryQuery.lastInsertId();
}

QVariant DBManager::addSoftwarePlatformLink(int softID, int platID)
{
	insertSoftwarePlatformQuery.addBindValue(softID);
	insertSoftwarePlatformQuery.addBindValue(platID);
	insertSoftwarePlatformQuery.exec();
	return insertSoftwarePlatformQuery.lastInsertId();
}

QVariant DBManager::addCategoryPlatformSoftwareRoleLink(int catID, int platID, int softID, int roleID)
{
	insertCatPlatSoftRoleQuery.addBindValue(catID);
	insertCatPlatSoftRoleQuery.addBindValue(platID);
	insertCatPlatSoftRoleQuery.addBindValue(softID);
	insertCatPlatSoftRoleQuery.addBindValue(roleID);
	insertCatPlatSoftRoleQuery.exec();
	return insertCatPlatSoftRoleQuery.lastInsertId();
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

QStringList DBManager::getPreferenceRoleList()
{
	QStringList roles;

	QLatin1String queryStr(R"(
		SELECT NAME
		FROM PREFERENCE_ROLE
		ORDER BY LEVEL
	)");
	QSqlQuery q(queryStr);
	while (q.next()) {
		QString prefRole = q.value(0).toString();
		roles << prefRole;
	}
	return roles;
}

QList<SoftwareItem> DBManager::getSoftwareItemList()
{
	QList<SoftwareItem> items;

	QLatin1String queryStr(R"(
		SELECT ID, NAME, LIMITATION, URL, NOTES
		FROM SOFTWARE
	)");
	QSqlQuery q(queryStr);
	while (q.next()) {
		QVariant softwareID = q.value(0);
		if (!softwareID.isValid()) {
			qCritical() << "Invalid software ID!";
			continue;
		}
		QStringList categories = getCategories(softwareID);
		QStringList platforms = getPlatforms(softwareID);
		QList<ContextualRole*> prefRoles = getPreferenceRoles(softwareID);
		QString name = q.value(1).toString();
		QString limitation = q.value(2).toString();
		QUrl url = QUrl(q.value(3).toString());
		QString notes = q.value(4).toString();

		SoftwareItem item(name, categories, platforms, prefRoles, limitation, url, notes);
		items << item;
	}
	return items;
}

QVariant DBManager::getCategoryID(const QString& category)
{
	selectIDForCategoryQuery.addBindValue(category);
	selectIDForCategoryQuery.exec();
	selectIDForCategoryQuery.next();
	return selectIDForCategoryQuery.value(0);
}

QVariant DBManager::getPlatformID(const QString& platform)
{
	selectIDForPlatformQuery.addBindValue(platform);
	selectIDForPlatformQuery.exec();
	selectIDForPlatformQuery.next();
	return selectIDForPlatformQuery.value(0);
}

QVariant DBManager::getPreferenceRoleID(const QString& prefRole)
{
	selectIDForPreferenceRoleQuery.addBindValue(prefRole);
	selectIDForPreferenceRoleQuery.exec();
	selectIDForPreferenceRoleQuery.next();
	return selectIDForPreferenceRoleQuery.value(0);
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

	selectCategoriesForSoftwareIDQuery = QSqlQuery(db);
	selectPlatformsForSoftwareIDQuery = QSqlQuery(db);
	selectCatPlatRoleListForSoftIDQuery = QSqlQuery(db);

	selectIDForCategoryQuery = QSqlQuery(db);
	selectIDForPlatformQuery = QSqlQuery(db);
	selectIDForPreferenceRoleQuery = QSqlQuery(db);
	selectCategoryForIDQuery = QSqlQuery(db);
	selectPlatformForIDQuery = QSqlQuery(db);
	selectPrefRoleForIDQuery = QSqlQuery(db);

	using namespace std;
	const QVector<std::pair<QSqlQuery*, QLatin1String>> queryToPreparePairList({ pair<QSqlQuery*, QLatin1String>(&insertSoftwareQuery, INSERT_SOFTWARE_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertCategoryQuery, INSERT_CATEGORY_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertPlatformQuery, INSERT_PLATFORM_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertRoleQuery, INSERT_ROLE_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertRequirementQuery, INSERT_REQUIREMENT_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwareCategoryQuery, INSERT_SOFTWARE_CATEGORY_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwarePlatformQuery, INSERT_SOFTWARE_PLATFORM_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertSoftwareRequirementQuery, INSERT_SOFTWARE_REQUIREMENT_SQL),
		pair<QSqlQuery*, QLatin1String>(&insertCatPlatSoftRoleQuery, INSERT_CAT_PLAT_SOFT_ROLE_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectCategoriesForSoftwareIDQuery, SELECT_CATEGORIES_FOR_SOFTWARE_ID_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectPlatformsForSoftwareIDQuery, SELECT_PLATFORMS_FOR_SOFTWARE_ID_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectCatPlatRoleListForSoftIDQuery, SELECT_CAT_PLAT_ROLE_LIST_FOR_SOFT_ID_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectIDForCategoryQuery, SELECT_ID_FOR_CATEGORY_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectIDForPlatformQuery, SELECT_ID_FOR_PLATFORM_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectIDForPreferenceRoleQuery, SELECT_ID_FOR_PREFERENCE_ROLE_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectCategoryForIDQuery, SELECT_CATEGORY_FOR_ID_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectPlatformForIDQuery, SELECT_PLATFORM_FOR_ID_SQL),
		pair<QSqlQuery*, QLatin1String>(&selectPrefRoleForIDQuery, SELECT_PREFERENCE_ROLE_FOR_ID_SQL) });

	for (const auto& qryPair : queryToPreparePairList) {
		QSqlQuery* q = qryPair.first;
		const QLatin1String& qStr = qryPair.second;
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

		addRole("Main", "Fulfills the need.", 1);
		addRole("Fallback", "Backup. Not necessarily a drop in replacement.", 100);
		addRole("Primary", "Meets most requirements, but cannot fulfill all requirements. "
						   "Needs other to make up the missing parts",
			1);
		addRole("Secondary", "Augments Primary towards fulfilling requirements.", 2);
		addRole("Tertiary", "Augments Primary & Secondary towards fulfilling requirements.", 3);
		addRole("Quaternary", "Augments Primary, Secondary & Tertiary towards fulfilling requirements. "
							  "If you need this level, your category might be too broad. "
							  "Consider breaking it up.",
			4);
		addRole("Inactive", "Not in consideration, kept as reference.", 200);
	}
}

QStringList DBManager::getCategories(QVariant& softwareID)
{
	QStringList categories;
	selectCategoriesForSoftwareIDQuery.addBindValue(softwareID);
	selectCategoriesForSoftwareIDQuery.exec();
	while (selectCategoriesForSoftwareIDQuery.next()) {
		categories << selectCategoriesForSoftwareIDQuery.value(0).toString();
	}
	return categories;
}

QStringList DBManager::getPlatforms(QVariant& softwareID)
{
	QStringList platforms;
	selectPlatformsForSoftwareIDQuery.addBindValue(softwareID);
	selectPlatformsForSoftwareIDQuery.exec();
	while (selectPlatformsForSoftwareIDQuery.next()) {
		platforms << selectPlatformsForSoftwareIDQuery.value(0).toString();
	}
	return platforms;
}

QList<ContextualRole*> DBManager::getPreferenceRoles(QVariant& softwareID)
{
	QList<ContextualRole*> prefRoles;
	selectCatPlatRoleListForSoftIDQuery.addBindValue(softwareID);
	selectCatPlatRoleListForSoftIDQuery.exec();
	while (selectCatPlatRoleListForSoftIDQuery.next()) {
		QVariant categoryID = selectCatPlatRoleListForSoftIDQuery.value(0);
		if (!categoryID.isValid()) {
			qCritical() << "Invalid Category ID!";
			continue;
		}
		QString category = getCategory(categoryID);

		QVariant platformID = selectCatPlatRoleListForSoftIDQuery.value(1);
		if (!platformID.isValid()) {
			qCritical() << "Invalid Platform ID!";
			continue;
		}
		QString platform = getPlatform(platformID);

		QVariant prefRoleID = selectCatPlatRoleListForSoftIDQuery.value(2);
		if (!prefRoleID.isValid()) {
			qCritical() << "Invalid Preference Role ID!";
			continue;
		}
		QString prefRole = getPreferenceRole(prefRoleID);

		prefRoles << new ContextualRole(category, platform, prefRole);
	}
	return prefRoles;
}

QString DBManager::getCategory(QVariant& categoryID)
{
	selectCategoryForIDQuery.addBindValue(categoryID);
	selectCategoryForIDQuery.exec();
	selectCategoryForIDQuery.next();
	return selectCategoryForIDQuery.value(0).toString();
}

QString DBManager::getPlatform(QVariant& platformID)
{
	selectPlatformForIDQuery.addBindValue(platformID);
	selectPlatformForIDQuery.exec();
	selectPlatformForIDQuery.next();
	return selectPlatformForIDQuery.value(0).toString();
}

QString DBManager::getPreferenceRole(QVariant& prefRoleID)
{
	selectPrefRoleForIDQuery.addBindValue(prefRoleID);
	selectPrefRoleForIDQuery.exec();
	selectPrefRoleForIDQuery.next();
	return selectPrefRoleForIDQuery.value(0).toString();
}
