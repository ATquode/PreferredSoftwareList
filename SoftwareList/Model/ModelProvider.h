// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "Model/CategoryListModel.h"
#include "Model/FilterOptionModel.h"
#include "Model/PlatformListModel.h"
#include "Model/SoftwareItemModel.h"

class ModelProvider : public QObject {
	Q_OBJECT
	Q_PROPERTY(CategoryListModel* catModel READ catModel CONSTANT)
	Q_PROPERTY(FilterOptionModel* filterOptionsModel READ filterOptionsModel CONSTANT)
	Q_PROPERTY(SoftwareItemModel* softSrcModel READ softSrcModel CONSTANT)
	QML_ELEMENT
	QML_SINGLETON
public:
	explicit ModelProvider(DBManager* dbManager, QObject* parent = nullptr);

	CategoryListModel* catModel()
	{
		return &categoryModel;
	}

	FilterOptionModel* filterOptionsModel()
	{
		return &filterModel;
	}

	SoftwareItemModel* softSrcModel()
	{
		return &softModel;
	}

private:
	CategoryListModel categoryModel;
	PlatformListModel platformModel;
	FilterOptionModel filterModel;
	SoftwareItemModel softModel;
};

#endif // MODELPROVIDER_H
