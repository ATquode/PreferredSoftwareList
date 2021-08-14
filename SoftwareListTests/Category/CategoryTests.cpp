// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Model/CategoryModel.h"
#include <gtest/gtest.h>

TEST(UnitTest, AddCategory)
{
	CategoryModel categoryModel;
	QString categoryName("Category dummy");
	emit categoryModel.categoryAdded(categoryName);
	QStringList categoryList = categoryModel.stringList();
	EXPECT_TRUE(categoryList.contains(categoryName));
}