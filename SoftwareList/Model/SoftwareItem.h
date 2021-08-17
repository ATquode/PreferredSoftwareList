// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEM_H
#define SOFTWAREITEM_H

#include <QString>
#include <QUrl>

class SoftwareItem {
public:
	SoftwareItem(QString name, QStringList categories, QStringList platforms,
		QString limitation, QUrl url, QString notes);

	QString name;
	QStringList categories;
	QStringList platforms;
	QString limitation;
	QUrl url;
	QString notes;
};

#endif // SOFTWAREITEM_H
