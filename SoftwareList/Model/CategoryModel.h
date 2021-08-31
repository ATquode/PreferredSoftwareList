// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include "DB/DBManager.h"

#include <QStringListModel>

class CategoryModel : public QStringListModel {
public:
	explicit CategoryModel(DBManager* dbManager, QObject* parent = nullptr);
	void addCategory(QString category);

private:
	DBManager* dbManager;
};

#endif // CATEGORYMODEL_H
