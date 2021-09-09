// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QMap>
#include <QString>

class Category {
public:
	Category(QString name, QMap<int, QString> reqMap);

	QString name;
	QMap<int, QString> requirementMap;
};

#endif // CATEGORY_H
