// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEM_H
#define SOFTWAREITEM_H

#include "Model/ContextualRole.h"

#include <QUrl>
#include <QtQml>

class SoftwareItem : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)
	Q_PROPERTY(QVariant preferenceRoles READ getPreferenceRoles WRITE setPreferenceRoles NOTIFY preferenceRolesChanged)
	Q_PROPERTY(QString limitation MEMBER limitation NOTIFY limitationChanged)
	Q_PROPERTY(QUrl url MEMBER url NOTIFY urlChanged)
	Q_PROPERTY(QString notes MEMBER notes NOTIFY notesChanged)
	QML_ELEMENT
public:
	explicit SoftwareItem(QObject* parent = nullptr) {};
	explicit SoftwareItem(QString name, QStringList categories, QStringList platforms,
		QList<ContextualRole*> roles, QString limitation,
		QUrl url, QString notes, QObject* parent = nullptr);

	QVariant getPreferenceRoles()
	{
		return QVariant::fromValue(preferenceRoles);
	}

	void setPreferenceRoles(QVariant prefRoleList)
	{
		preferenceRoles = prefRoleList.value<QList<ContextualRole*>>();
	}

	QString name;
	QStringList categories;
	QStringList platforms;
	QList<ContextualRole*> preferenceRoles;
	QString limitation;
	QUrl url;
	QString notes;

signals:
	void nameChanged();
	void preferenceRolesChanged();
	void limitationChanged();
	void urlChanged();
	void notesChanged();
};

#endif // SOFTWAREITEM_H
