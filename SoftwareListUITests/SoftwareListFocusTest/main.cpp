// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "UITestServer.h"

#include "Model/ModelProvider.h"
#include "Model/SoftwareItemProxyModel.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <Spix/QtQmlBot.h>

TEST(UITest, SoftwareListFocusTest)
{
	std::string splitViewPath = "mainWindow/splitView";
	std::string catListPath = splitViewPath + "/catList";
	std::string softListPath = splitViewPath + "/softList";
	auto catListItemPath = spix::ItemPath(catListPath);
	auto softListItemPath = spix::ItemPath(softListPath);
	std::string selectedColor = srv->getStringProperty(catListItemPath, "selectedColor");
	std::string defaultColor = srv->getStringProperty(softListItemPath, "defaultColor");
	std::string focusedColor = srv->getStringProperty(softListItemPath, "focusedColor");

	// 1st item in Category List should be auto selected
	std::string item0Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, selectedColor);

	// right arrow should move focus to Software List
	srv->enterKey(catListItemPath, Qt::Key_Right, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	item0Color = srv->getStringProperty(spix::ItemPath(softListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, focusedColor);

	// down arrow should focus on the 2nd item in Software List
	srv->enterKey(softListItemPath, Qt::Key_Down, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	std::string item1Color = srv->getStringProperty(spix::ItemPath(softListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, focusedColor);
	item0Color = srv->getStringProperty(spix::ItemPath(softListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, defaultColor);

	srv->quit();
}

int main(int argc, char* argv[])
{
	// Init Qt Qml Application
	QGuiApplication app(argc, argv);

	// Setup Data
	ModelProvider modelProvider(nullptr);

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
