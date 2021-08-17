// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItem.h"

// TODO: Category Requirement, Preference Roles
SoftwareItem::SoftwareItem(QString name, QStringList categories,
	QStringList platforms, QString limitation, QUrl url,
	QString notes)
	: name(name)
	, categories(categories)
	, platforms(platforms)
	, limitation(limitation)
	, url(url)
	, notes(notes)
{
}
