// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CONTEXTUALROLE_H
#define CONTEXTUALROLE_H

#include <QObject>
#include <QString>

class ContextualRole : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString platform MEMBER platform NOTIFY platformChanged)
	Q_PROPERTY(QString prefRole MEMBER prefRole NOTIFY prefRoleChanged)
public:
	QString category;
	QString platform;
	QString prefRole;

	ContextualRole(QObject* parent = nullptr) { }

	ContextualRole(QString cat, QString plat, QString role, QObject* parent = nullptr)
		: QObject(parent)
		, prefRole(role)
		, category(cat)
		, platform(plat)
	{
	}

signals:
	void platformChanged();
	void prefRoleChanged();
};

#endif // CONTEXTUALROLE_H
