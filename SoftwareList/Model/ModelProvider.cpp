// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "ModelProvider.h"

ModelProvider::ModelProvider(DBManager* dbManager, QObject* parent)
	: QObject(parent)
	, categoryModel(dbManager)
	, platformModel(dbManager)
	, prefRoleModel(dbManager)
	, filterModel(platformModel.stringList(), prefRoleModel.stringList())
	, softModel(dbManager)
{
}
