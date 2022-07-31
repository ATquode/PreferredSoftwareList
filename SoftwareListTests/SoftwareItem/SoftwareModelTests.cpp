// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Model/SoftwareItemModel.h"

#include <gtest/gtest.h>

TEST(UnitTest, AddSoftwareItem)
{
	SoftwareItemModel softModel(nullptr);
	QString swName("dummy soft");
	SoftwareItem* item = new SoftwareItem(swName, QStringList(""), QStringList(""), QList<ContextualRole*>(), "", QUrl(), "");
	softModel.addItem(item);
	int lastIndex = softModel.rowCount() - 1;
	QModelIndex index = softModel.index(lastIndex);
	QString softName = softModel.data(index, SWItemRole::NameRole).toString();
	EXPECT_TRUE(swName.compare(softName) == 0);
}
