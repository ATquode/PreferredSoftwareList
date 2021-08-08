// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QStringListModel>

class CategoryModel : public QStringListModel {
public:
	CategoryModel(QObject* parent = nullptr);
};

#endif // CATEGORYMODEL_H
