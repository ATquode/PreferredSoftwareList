// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Model/CategoryListModel.h"

#include <gtest/gtest.h>

TEST(UnitTest, AddCategory)
{
	CategoryListModel categoryModel(nullptr);
	QString categoryName("Category dummy");
	categoryModel.addCategory(categoryName, QStringList());
	QStringList categoryList = categoryModel.stringList();
	EXPECT_TRUE(categoryList.contains(categoryName));
}
