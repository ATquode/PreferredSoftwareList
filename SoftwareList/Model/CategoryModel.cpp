// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "CategoryModel.h"

CategoryModel::CategoryModel(DBManager* dbManager, QObject* parent)
	: QStringListModel(parent)
{
	this->dbManager = dbManager;
	QStringList list;
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
	list << "All";
#endif /* !Q_OS_ANDROID && !Q_OS_IOS */
	if (dbManager != nullptr) {
		dbManager->addCategory("Category 1");
		dbManager->addCategory("Category 2");

		list << dbManager->getCategoryList();
	}
	setStringList(list);
}

void CategoryModel::addCategory(QString category)
{
	if (dbManager != nullptr) {
		QVariant id = dbManager->addCategory(category);
		if (!id.isValid()) {
			return;
		}
	}

	if (insertRow(rowCount())) {
		QModelIndex idx = index(rowCount() - 1);
		setData(idx, category);
	}
}
