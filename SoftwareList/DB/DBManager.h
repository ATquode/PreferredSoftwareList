// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "Model/SoftwareItem.h"

#include <QtSql>

class DBManager : public QObject {
	Q_OBJECT
public:
	explicit DBManager(QObject* parent = nullptr);

	QVariant addCategory(QString name);
	QVariant addRequirement(QString req, int categoryID);
	QVariant addPlatform(QString name);
	QVariant addRole(QString name, QString description, int level);
	QVariant addSoftwareItem(const SoftwareItem& item);
	QVariant addSoftwareCategoryLink(int softID, int catID);
	QVariant addSoftwarePlatformLink(int softID, int platID);
	QVariant addCategoryPlatformSoftwareRoleLink(int catID, int platID, int softID, int roleID);

	QStringList getCategoryList();
	QStringList getPlatformList();
	QList<SoftwareItem> getSoftwareItemList();

	QVariant getCategoryID(const QString& category);
	QVariant getPlatformID(const QString& platform);
	QVariant getPreferenceRoleID(const QString& prefRole);

private:
	const QLatin1String SOFTWARE_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS SOFTWARE(
			ID INTEGER PRIMARY KEY,
			NAME TEXT NOT NULL,
			LIMITATION TEXT,
			URL TEXT,
			NOTES TEXT
		)
	)");

	const QLatin1String CATEGORY_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS CATEGORY(
			ID INTEGER PRIMARY KEY,
			NAME TEXT NOT NULL
		)
	)");

	const QLatin1String PLATFORM_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS PLATFORM(
			ID INTEGER PRIMARY KEY,
			NAME TEXT NOT NULL
		)
	)");

	const QLatin1String PREFERENCE_ROLE_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS PREFERENCE_ROLE(
			ID INTEGER PRIMARY KEY,
			NAME TEXT NOT NULL,
			DESCRIPTION TEXT NOT NULL,
			LEVEL INTEGER NOT NULL
		)
	)");

	const QLatin1String REQUIREMENT_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS REQUIREMENT(
			ID INTEGER PRIMARY KEY,
			NAME TEXT NOT NULL,
			CATEGORY_ID INTEGER NOT NULL,
			FOREIGN KEY (CATEGORY_ID)
				REFERENCES CATEGORY (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE
		)
	)");

	const QLatin1String SOFTWARE_CATEGORY_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS SOFTWARE_CATEGORY(
			SOFTWARE_ID INTEGER,
			CATEGORY_ID INTEGER,
			PRIMARY KEY (SOFTWARE_ID, CATEGORY_ID),
			FOREIGN KEY (SOFTWARE_ID)
				REFERENCES SOFTWARE (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (CATEGORY_ID)
				REFERENCES CATEGORY (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE
		)
	)");

	const QLatin1String SOFTWARE_PLATFORM_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS SOFTWARE_PLATFORM(
			SOFTWARE_ID INTEGER,
			PLATFORM_ID INTEGER,
			PRIMARY KEY (SOFTWARE_ID, PLATFORM_ID),
			FOREIGN KEY (SOFTWARE_ID)
				REFERENCES SOFTWARE (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (PLATFORM_ID)
				REFERENCES PLATFORM (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE
		)
	)");

	const QLatin1String SOFTWARE_REQUIREMENT_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS SOFTWARE_REQUIREMENT(
			SOFTWARE_ID INTEGER,
			REQUIREMENT_ID INTEGER,
			PRIMARY KEY (SOFTWARE_ID, REQUIREMENT_ID),
			FOREIGN KEY (SOFTWARE_ID)
				REFERENCES SOFTWARE (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (REQUIREMENT_ID)
				REFERENCES REQUIREMENT (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE
		)
	)");

	const QLatin1String CAT_PLAT_SOFT_ROLE_TABLE_SQL = QLatin1String(R"(
		CREATE TABLE IF NOT EXISTS CAT_PLAT_SOFT_ROLE(
			CATEGORY_ID INTEGER,
			PLATFORM_ID INTEGER,
			SOFTWARE_ID INTEGER,
			ROLE_ID INTEGER,
			PRIMARY KEY (CATEGORY_ID, PLATFORM_ID, SOFTWARE_ID, ROLE_ID),
			FOREIGN KEY (CATEGORY_ID)
				REFERENCES CATEGORY (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (PLATFORM_ID)
				REFERENCES PLATFORM (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (SOFTWARE_ID)
				REFERENCES SOFTWARE (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE,
			FOREIGN KEY (ROLE_ID)
				REFERENCES PREFERENCE_ROLE (ID)
				ON DELETE CASCADE
				ON UPDATE CASCADE
		)
	)");

	const QLatin1String INSERT_SOFTWARE_SQL = QLatin1String(R"(
		INSERT INTO SOFTWARE (NAME, LIMITATION, URL, NOTES)
		VALUES(?, ?, ?, ?)
	)");

	const QLatin1String INSERT_CATEGORY_SQL = QLatin1String(R"(
		INSERT INTO CATEGORY (NAME)
		VALUES(?)
	)");

	const QLatin1String INSERT_PLATFORM_SQL = QLatin1String(R"(
		INSERT INTO PLATFORM (NAME)
		VALUES(?)
	)");

	const QLatin1String INSERT_ROLE_SQL = QLatin1String(R"(
		INSERT INTO PREFERENCE_ROLE (NAME, DESCRIPTION, LEVEL)
		VALUES(?, ?, ?)
	)");

	const QLatin1String INSERT_REQUIREMENT_SQL = QLatin1String(R"(
		INSERT INTO REQUIREMENT (NAME, CATEGORY_ID)
		VALUES(?, ?)
	)");

	const QLatin1String INSERT_SOFTWARE_CATEGORY_SQL = QLatin1String(R"(
		INSERT INTO SOFTWARE_CATEGORY (SOFTWARE_ID, CATEGORY_ID)
		VALUES(?, ?)
	)");

	const QLatin1String INSERT_SOFTWARE_PLATFORM_SQL = QLatin1String(R"(
		INSERT INTO SOFTWARE_PLATFORM (SOFTWARE_ID, PLATFORM_ID)
		VALUES(?, ?)
	)");

	const QLatin1String INSERT_SOFTWARE_REQUIREMENT_SQL = QLatin1String(R"(
		INSERT INTO SOFTWARE_REQUIREMENT (SOFTWARE_ID, REQUIREMENT_ID)
		VALUES(?, ?)
	)");

	const QLatin1String INSERT_CAT_PLAT_SOFT_ROLE_SQL = QLatin1String(R"(
		INSERT INTO CAT_PLAT_SOFT_ROLE (CATEGORY_ID, PLATFORM_ID, SOFTWARE_ID, ROLE_ID)
		VALUES(?, ?, ?, ?)
	)");

	const QLatin1String SELECT_CATEGORIES_FOR_SOFTWARE_ID_SQL = QLatin1String(R"(
		SELECT NAME
		FROM CATEGORY
		WHERE ID IN (
			SELECT CATEGORY_ID
			FROM SOFTWARE_CATEGORY
			WHERE SOFTWARE_ID = ?
		)
	)");

	const QLatin1String SELECT_PLATFORMS_FOR_SOFTWARE_ID_SQL = QLatin1String(R"(
		SELECT NAME
		FROM PLATFORM
		WHERE ID IN (
			SELECT PLATFORM_ID
			FROM SOFTWARE_PLATFORM
			WHERE SOFTWARE_ID = ?
		)
	)");

	const QLatin1String SELECT_CAT_PLAT_ROLE_LIST_FOR_SOFT_ID_SQL = QLatin1String(R"(
		SELECT CATEGORY_ID, PLATFORM_ID, ROLE_ID
		FROM CAT_PLAT_SOFT_ROLE
		WHERE SOFTWARE_ID = ?
	)");

	const QLatin1String SELECT_ID_FOR_CATEGORY_SQL = QLatin1String(R"(
		SELECT ID
		FROM CATEGORY
		WHERE NAME = ?
	)");

	const QLatin1String SELECT_ID_FOR_PLATFORM_SQL = QLatin1String(R"(
		SELECT ID
		FROM PLATFORM
		WHERE NAME = ?
	)");

	const QLatin1String SELECT_ID_FOR_PREFERENCE_ROLE_SQL = QLatin1String(R"(
		SELECT ID
		FROM PREFERENCE_ROLE
		WHERE NAME = ?
	)");

	const QLatin1String SELECT_CATEGORY_FOR_ID_SQL = QLatin1String(R"(
		SELECT NAME
		FROM CATEGORY
		WHERE ID = ?
	)");

	const QLatin1String SELECT_PLATFORM_FOR_ID_SQL = QLatin1String(R"(
		SELECT NAME
		FROM PLATFORM
		WHERE ID = ?
	)");

	const QLatin1String SELECT_PREFERENCE_ROLE_FOR_ID_SQL = QLatin1String(R"(
		SELECT NAME
		FROM PREFERENCE_ROLE
		WHERE ID = ?
	)");

	QSqlQuery insertSoftwareQuery,
		insertCategoryQuery,
		insertPlatformQuery,
		insertRoleQuery,
		insertRequirementQuery,
		insertSoftwareCategoryQuery,
		insertSoftwarePlatformQuery,
		insertSoftwareRequirementQuery,
		insertCatPlatSoftRoleQuery;
	QSqlQuery selectCategoriesForSoftwareIDQuery,
		selectPlatformsForSoftwareIDQuery,
		selectCatPlatRoleListForSoftIDQuery;
	QSqlQuery selectIDForCategoryQuery,
		selectIDForPlatformQuery,
		selectIDForPreferenceRoleQuery,
		selectCategoryForIDQuery,
		selectPlatformForIDQuery,
		selectPrefRoleForIDQuery;

	QSqlError createTables();
	QSqlError prepareStatements(QSqlDatabase& db);

	/**
	 * @brief Populate database with default data. If relevant data
	 * already exists, it won't modify the DB. 
	 */
	void populateDB();

	QStringList getCategories(QVariant& softwareID);
	QStringList getPlatforms(QVariant& softwareID);
	QList<ContextualRole*> getPreferenceRoles(QVariant& softwareID);
	QString getCategory(QVariant& categoryID);
	QString getPlatform(QVariant& platformID);
	QString getPreferenceRole(QVariant& prefRoleID);
};

#endif // DBMANAGER_H
