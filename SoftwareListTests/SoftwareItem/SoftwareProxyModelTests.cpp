// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Model/SoftwareItemModel.h"
#include "Model/SoftwareItemProxyModel.h"

#include <gtest/gtest.h>

class SoftwareItemProxyModelTest : public SoftwareItemProxyModel {
public:
	bool filterAccepts(int row)
	{
		return filterAcceptsRow(row, QModelIndex());
	}
};

TEST(UnitTest, FilterOrCondition)
{
	SoftwareItemProxyModelTest proxyModel;
	SoftwareItemModel softModel(nullptr);
	proxyModel.setSourceModel(&softModel);

	QString plat_linux("Linux");
	QString plat_android("android");

	SoftwareItem item1("Soft1", QStringList(), QStringList(plat_linux), "", QUrl(), "");
	softModel.addItem(item1);
	int lastIndex = softModel.rowCount() - 1;

	proxyModel.addFilter(SWItemRole::PlatformRole, plat_android);
	EXPECT_FALSE(proxyModel.filterAccepts(lastIndex));
	proxyModel.addFilter(SWItemRole::PlatformRole, plat_linux);
	EXPECT_TRUE(proxyModel.filterAccepts(lastIndex)) << "Same role should have OR condition";
}

TEST(UnitTest, FilterAndCondition)
{
	SoftwareItemProxyModelTest proxyModel;
	SoftwareItemModel softModel(nullptr);
	proxyModel.setSourceModel(&softModel);

	QString category1("Category 1");
	QString plat_linux("Linux");
	QString plat_windows("Windows");

	SoftwareItem item1("Soft1", QStringList(category1), QStringList(plat_windows), "", QUrl(), "");
	softModel.addItem(item1);
	int lastIndex = softModel.rowCount() - 1;

	proxyModel.addFilter(SWItemRole::CategoryRole, category1);
	proxyModel.addFilter(SWItemRole::PlatformRole, plat_linux);
	EXPECT_FALSE(proxyModel.filterAccepts(lastIndex)) << "Different roles should have AND condition";

	proxyModel.addFilter(SWItemRole::PlatformRole, plat_windows);
	// OR condition activates
	EXPECT_TRUE(proxyModel.filterAccepts(lastIndex)) << "Same role should have OR condition";
}
