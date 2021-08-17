// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "CategoryModel.h"

CategoryModel::CategoryModel(QObject* parent)
	: QStringListModel(parent)
{
	QStringList list;
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
	list << "All";
#endif /* !Q_OS_ANDROID && !Q_OS_IOS */
	list << "Category 1"
		 << "Category 2";
	setStringList(list);
}

void CategoryModel::addCategory(QString category)
{
	if (insertRow(rowCount())) {
		QModelIndex idx = index(rowCount() - 1);
		setData(idx, category);
	}
}
