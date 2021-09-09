// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "CategoryListModel.h"

CategoryListModel::CategoryListModel(DBManager* dbManager, QObject* parent)
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

void CategoryListModel::addCategory(QString category, QStringList requirements)
{
	if (dbManager != nullptr) {
		QVariant id = dbManager->addCategory(category);
		if (!id.isValid()) {
			qCritical() << "Failed to insert Category: " << category;
			return;
		}
		bool ok;
		int categoryID = id.toInt(&ok);
		if (!ok) {
			qCritical() << "Failed to convert Category ID to int for Category: " << category;
			return;
		}

		for (const auto& req : qAsConst(requirements)) {
			id = dbManager->addRequirement(req, categoryID);
			if (!id.isValid()) {
				qCritical() << "Failed to insert Requirement: " << req;
				// TODO: Offer retry for the failed ones, cancel to rollback
			}
		}
	}

	if (insertRow(rowCount())) {
		QModelIndex idx = index(rowCount() - 1);
		setData(idx, category);
	}
}
