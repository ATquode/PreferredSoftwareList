// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEM_H
#define SOFTWAREITEM_H

#include <QObject>
#include <QString>
#include <QUrl>

class ContextualRole : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString platform READ getPlatform CONSTANT)
	Q_PROPERTY(QString prefRole MEMBER prefRole NOTIFY prefRoleChanged)
public:
	QString prefRole;

	ContextualRole(QString cat, QString plat, QString role, QObject* parent = nullptr)
		: QObject(parent)
		, prefRole(role)
		, category(cat)
		, platform(plat)
	{
	}

	QString getPlatform()
	{
		return platform;
	}

signals:
	void prefRoleChanged();

private:
	QString category;
	QString platform;
};

class SoftwareItem {
public:
	SoftwareItem(QString name, QStringList categories, QStringList platforms,
		QList<ContextualRole*> roles, QString limitation,
		QUrl url, QString notes);

	QString name;
	QStringList categories;
	QStringList platforms;
	QList<ContextualRole*> preferenceRoles;
	QString limitation;
	QUrl url;
	QString notes;
};

#endif // SOFTWAREITEM_H
