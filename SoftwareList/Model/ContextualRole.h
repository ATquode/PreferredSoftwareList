// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CONTEXTUALROLE_H
#define CONTEXTUALROLE_H

#include <QObject>
#include <QString>

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

	const QString& getCategory() const
	{
		return category;
	}

	const QString& getPlatform() const
	{
		return platform;
	}

signals:
	void prefRoleChanged();

private:
	QString category;
	QString platform;
};

#endif // CONTEXTUALROLE_H
