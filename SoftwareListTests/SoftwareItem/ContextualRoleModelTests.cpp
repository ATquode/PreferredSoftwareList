// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Model/ContextualRoleTableModel.h"

#include <gtest/gtest.h>

TEST(UnitTest, CategoryChanged)
{
	ContextualRoleTableModel* model = new ContextualRoleTableModel();
	auto ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	// 0 item at creation
	EXPECT_EQ(ctxList.count(), 0);
	model->componentComplete();
	// 1 item after component completion
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with high index will be ignored
	QString catStr = "Category 1";
	model->onCategoryChanged(catStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with valid index
	model->onCategoryChanged(catStr, 1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	EXPECT_STREQ(ctxList[0]->category.toStdString().c_str(), catStr.toStdString().c_str());
	// change item with index zero will be ignored
	catStr = "Category 0";
	model->onCategoryChanged(catStr, 0);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with negative index will be ignored
	model->onCategoryChanged(catStr, -1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	model->onCategoryChanged(catStr, -3);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// add another row
	model->onAddRowClicked();
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	// change new item
	catStr = "Category 2";
	model->onCategoryChanged(catStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	EXPECT_STREQ(ctxList[1]->category.toStdString().c_str(), catStr.toStdString().c_str());
}

TEST(UnitTest, PlatformChanged)
{
	ContextualRoleTableModel* model = new ContextualRoleTableModel();
	auto ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	// 0 item at creation
	EXPECT_EQ(ctxList.count(), 0);
	model->componentComplete();
	// 1 item after component completion
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with high index will be ignored
	QString platStr = "Platform 1";
	model->onPlatformChanged(platStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with valid index
	model->onPlatformChanged(platStr, 1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	EXPECT_STREQ(ctxList[0]->platform.toStdString().c_str(), platStr.toStdString().c_str());
	// change item with index zero will be ignored
	platStr = "Platform 0";
	model->onPlatformChanged(platStr, 0);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with negative index will be ignored
	model->onPlatformChanged(platStr, -1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	model->onPlatformChanged(platStr, -3);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// add another row
	model->onAddRowClicked();
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	// change new item
	platStr = "Platform 2";
	model->onPlatformChanged(platStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	EXPECT_STREQ(ctxList[1]->platform.toStdString().c_str(), platStr.toStdString().c_str());
}

TEST(UnitTest, PrefRoleChanged)
{
	ContextualRoleTableModel* model = new ContextualRoleTableModel();
	auto ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	// 0 item at creation
	EXPECT_EQ(ctxList.count(), 0);
	model->componentComplete();
	// 1 item after component completion
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with high index will be ignored
	QString prefRoleStr = "Preference Role 1";
	model->onPrefRoleChanged(prefRoleStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with valid index
	model->onPrefRoleChanged(prefRoleStr, 1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	EXPECT_STREQ(ctxList[0]->prefRole.toStdString().c_str(), prefRoleStr.toStdString().c_str());
	// change item with index zero will be ignored
	prefRoleStr = "Preference Role 0";
	model->onPrefRoleChanged(prefRoleStr, 0);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// change item with negative index will be ignored
	model->onPrefRoleChanged(prefRoleStr, -1);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	model->onPrefRoleChanged(prefRoleStr, -3);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 1);
	// add another row
	model->onAddRowClicked();
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	// change new item
	prefRoleStr = "Preference Role 2";
	model->onPrefRoleChanged(prefRoleStr, 2);
	ctxList = model->contextRoles().value<QList<ContextualRole*>>();
	EXPECT_EQ(ctxList.count(), 2);
	EXPECT_STREQ(ctxList[1]->prefRole.toStdString().c_str(), prefRoleStr.toStdString().c_str());
}
