// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "Model/CategoryListModel.h"
#include "Model/SoftwareItemModel.h"

class ModelProvider : public QObject {
public:
	explicit ModelProvider(DBManager* dbManager, QObject* parent = nullptr);

	SoftwareItemModel softModel;
	CategoryListModel categoryModel;
};

#endif // MODELPROVIDER_H
