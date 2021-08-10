// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include <QStringListModel>

class CategoryModel : public QStringListModel {
	Q_OBJECT
public:
	CategoryModel(QObject* parent = nullptr);

signals:
	void categoryAdded(QString category);

public slots:
	void onCategoryAdd(QString category);
};

#endif // CATEGORYMODEL_H
