// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "PreferenceRoleListModel.h"

PreferenceRoleListModel::PreferenceRoleListModel(DBManager* dbManager, QObject* parent)
	: QStringListModel { parent }
{
	this->dbManager = dbManager;
	QStringList list;
	if (dbManager != nullptr) {
		list = dbManager->getPreferenceRoleList();
	}
	setStringList(list);
}
