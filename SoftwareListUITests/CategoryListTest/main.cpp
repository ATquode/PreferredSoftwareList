// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "UITestServer.h"

#include "Model/ModelProvider.h"
#include "Model/SoftwareItemProxyModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <Spix/QtQmlBot.h>

TEST(UITest, CategoryListHoverFocusTest)
{
	std::string catListPath = "mainWindow/splitView/catList";
	auto catListItemPath = spix::ItemPath(catListPath);
	std::string defaultColor = srv->getStringProperty(catListItemPath, "defaultColor");
	std::string selectedColor = srv->getStringProperty(catListItemPath, "selectedColor");
	std::string hoverFocusColor = srv->getStringProperty(catListItemPath, "hoverColor");

	// 1st item in Category List should be auto selected
	std::string item0Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, selectedColor);
	// Can't test border color, not even by setting objectName

	// down arrow should focus on the 2nd item in Category List
	srv->enterKey(catListItemPath, Qt::Key_Down, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	std::string item1Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, hoverFocusColor);
	// 1st item should still retain selected color
	item0Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, selectedColor);

	// non-selected, non-focused item should have default color
	std::string item2Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_2"), "color");
	EXPECT_EQ(item2Color, defaultColor);

	// pressing return should select the focused item
	srv->enterKey(catListItemPath, Qt::Key_Return, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	item1Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, selectedColor);
	item0Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, defaultColor);

	// mouse click will select item
	srv->mouseClick(spix::ItemPath(catListPath + "/listItem_2"));
	srv->wait(std::chrono::milliseconds(500));
	item2Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_2"), "color");
	EXPECT_EQ(item2Color, selectedColor);
	item1Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, defaultColor);

	// mouse hovered on selected, arrow up to focus previous item, and select by press return should change the hovered item to unselected

	srv->quit();
}

int main(int argc, char* argv[])
{
	// Init Qt Qml Application
	QGuiApplication app(argc, argv);

	// Setup Data
	ModelProvider modelProvider(nullptr);
	modelProvider.catModel()->addCategory("Category A", QStringList());
	modelProvider.catModel()->addCategory("Category B", QStringList());
	modelProvider.catModel()->addCategory("Category C", QStringList());

	// Setup Qml Engine
	QQmlApplicationEngine engine;
	qmlRegisterUncreatableType<SWItemRole>("SWList", 1, 0, "SWItemRole", "Enum wrapper not creatable");
	qmlRegisterSingletonInstance("SWList", 1, 0, "ModelProvider", &modelProvider);
	qmlRegisterType<SoftwareItemProxyModel>("SWList", 1, 0, "SoftProxyModel");
	engine.load(QUrl(QStringLiteral("qrc:/UI/MainWindow.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	// Init Test Server
	UITestServer server(argc, argv);
	auto bot = new spix::QtQmlBot();
	bot->runTestServer(server);

	app.exec();
	return server.getResult();
}
