// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "Model/CategoryListModel.h"
#include "Model/SoftwareItemModel.h"

class ModelProvider : public QObject {
	Q_OBJECT
	Q_PROPERTY(CategoryListModel* catModel READ catModel CONSTANT)
	Q_PROPERTY(SoftwareItemModel* softSrcModel READ softSrcModel CONSTANT)
	QML_ELEMENT
	QML_SINGLETON
public:
	explicit ModelProvider(DBManager* dbManager, QObject* parent = nullptr);

	CategoryListModel* catModel()
	{
		return &categoryModel;
	}

	SoftwareItemModel* softSrcModel()
	{
		return &softModel;
	}

private:
	CategoryListModel categoryModel;
	SoftwareItemModel softModel;
};

#endif // MODELPROVIDER_H
