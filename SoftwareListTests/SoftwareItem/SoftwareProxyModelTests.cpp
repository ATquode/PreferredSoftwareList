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

	SoftwareItem* item1 = new SoftwareItem("Soft1", QStringList(), QStringList(plat_linux), QList<ContextualRole*>(), "", QUrl(), "");
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

	SoftwareItem* item1 = new SoftwareItem("Soft1", QStringList(category1), QStringList(plat_windows), QList<ContextualRole*>(), "", QUrl(), "");
	softModel.addItem(item1);
	int lastIndex = softModel.rowCount() - 1;

	proxyModel.addFilter(SWItemRole::CategoryRole, category1);
	proxyModel.addFilter(SWItemRole::PlatformRole, plat_linux);
	EXPECT_FALSE(proxyModel.filterAccepts(lastIndex)) << "Different roles should have AND condition";

	proxyModel.addFilter(SWItemRole::PlatformRole, plat_windows);
	// OR condition activates
	EXPECT_TRUE(proxyModel.filterAccepts(lastIndex)) << "Same role should have OR condition";
}

TEST(UnitTest, FilterPreference)
{
	SoftwareItemProxyModelTest proxyModel;
	SoftwareItemModel softModel(nullptr);
	proxyModel.setSourceModel(&softModel);

	QString category1("Category 1");
	QString category2("Category 2");
	QString plat_mac("macOS");
	QString role_main("Main");

	SoftwareItem* item1 = new SoftwareItem("Soft1", QStringList(category1), QStringList(plat_mac),
		QList<ContextualRole*>({ new ContextualRole(category1, plat_mac, role_main) }), "", QUrl(), "");
	softModel.addItem(item1);
	int lastIndex = softModel.rowCount() - 1;

	proxyModel.addFilter(SWItemRole::PreferenceRole, role_main);
	EXPECT_TRUE(proxyModel.filterAccepts(lastIndex)) << "Only preference role filter should not care about category or platform";

	proxyModel.addFilter(SWItemRole::CategoryRole, category2);
	EXPECT_FALSE(proxyModel.filterAccepts(lastIndex)) << "Preference match won't be accepted "
														 "if one/more category/platform filter is active and none of them match";

	proxyModel.addFilter(SWItemRole::CategoryRole, category1);
	EXPECT_TRUE(proxyModel.filterAccepts(lastIndex)) << "Preference match should be accepted "
														"if one/more category/platform filter is active and one of them (1 from category, 1 from platform) matches";
}
