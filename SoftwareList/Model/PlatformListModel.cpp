// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "PlatformListModel.h"

PlatformListModel::PlatformListModel(DBManager* dbManager, QObject* parent)
	: QStringListModel(parent)
{
	this->dbManager = dbManager;
	QStringList list;
	if (dbManager != nullptr) {
		list = dbManager->getPlatformList();
	}
	setStringList(list);
}
