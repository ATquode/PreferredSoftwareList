// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItem.h"

// TODO: Category Requirement
SoftwareItem::SoftwareItem(QString name, QStringList categories,
	QStringList platforms, QList<ContextualRole*> roles,
	QString limitation, QUrl url,
	QString notes)
	: name(name)
	, categories(categories)
	, platforms(platforms)
	, preferenceRoles(roles)
	, limitation(limitation)
	, url(url)
	, notes(notes)
{
}
