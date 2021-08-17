// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SWITEMROLE_H
#define SWITEMROLE_H

#include <QObject>

class SWItemRole {
	Q_GADGET
public:
	enum ItemRole {
		NameRole = Qt::UserRole + 1,
		CategoryRole,
		PlatformRole,
		LimitationRole,
		UrlRole,
		NotesRole
	};
	Q_ENUM(ItemRole);

private:
	explicit SWItemRole() { }
};

#endif // SWITEMROLE_H
