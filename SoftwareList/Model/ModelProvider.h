// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "Model/CategoryListModel.h"
#include "Model/FilterOptionModel.h"
#include "Model/PlatformListModel.h"
#include "Model/PreferenceRoleListModel.h"
#include "Model/SoftwareItemModel.h"

class ModelProvider : public QObject {
	Q_OBJECT
	/** catModel contains all categories, and the category "All" in relevant platform. */
	Q_PROPERTY(CategoryListModel* catModel READ catModel CONSTANT)
	/** Category List, excluding the category "All". */
	Q_PROPERTY(QStringList catList READ catList CONSTANT)
	Q_PROPERTY(PlatformListModel* platformModel READ platModel CONSTANT)
	Q_PROPERTY(PreferenceRoleListModel* preferenceRoleModel READ preferenceRoleModel CONSTANT)
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

	QStringList catList()
	{
		QStringList list = categoryModel.stringList();
#if !defined(Q_OS_ANDROID) && !defined(Q_OS_IOS)
		list.removeFirst(); // removing the category "All"
#endif /* !Q_OS_ANDROID && !Q_OS_IOS */
		return list;
	}

	PlatformListModel* platModel()
	{
		return &platformModel;
	}

	PreferenceRoleListModel* preferenceRoleModel()
	{
		return &prefRoleModel;
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
	PreferenceRoleListModel prefRoleModel;
	FilterOptionModel filterModel;
	SoftwareItemModel softModel;
};

#endif // MODELPROVIDER_H
