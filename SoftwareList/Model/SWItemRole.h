// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SWITEMROLE_H
#define SWITEMROLE_H

#include <QObject>
#include <QtQml>

class SWItemRole {
	Q_GADGET
	QML_ELEMENT
	QML_UNCREATABLE("Enum wrapper not creatable")
public:
	enum ItemRole {
		NameRole = Qt::UserRole + 1,
		CategoryRole,
		PlatformRole,
		LimitationRole,
		UrlRole,
		NotesRole,
		RequirementRole
	};
	Q_ENUM(ItemRole);

	enum FilterRole {
		FilterItemRole = Qt::UserRole + 1,
		TypeRole,
		OptionRole
	};
	Q_ENUM(FilterRole);

private:
	explicit SWItemRole() { }
};

#endif // SWITEMROLE_H
