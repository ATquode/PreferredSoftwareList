// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <Spix/QtQmlBot.h>

#include <atomic>
#include <gtest/gtest.h>

class UITestServer; //TODO: Remove after putting the definition in a new file
static UITestServer* srv;

class UITestServer : public spix::TestServer {
public:
	UITestServer(int _argc, char* _argv[])
		: argc(_argc)
		, argv(_argv)
	{
	}

	int getResult()
	{
		return result.load();
	}

protected:
	int argc;
	char** argv;
	std::atomic<int> result { 0 };

	void executeTest() override
	{
		srv = this;
		::testing::InitGoogleTest(&argc, argv);
		int testResult = RUN_ALL_TESTS();
		result.store(testResult);
	}
};

TEST(UITest, CategoryListTest)
{
	std::string catListPath = "mainWindow/splitView/categoryList";
	auto catListItemPath = spix::ItemPath(catListPath);
	std::string defaultColor = srv->getStringProperty(catListItemPath, "defaultColor");
	std::string selectedColor = srv->getStringProperty(catListItemPath, "selectedColor");
	std::string hoverColor = srv->getStringProperty(catListItemPath, "hoverColor");

	std::string item0Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_0"), "color");
	EXPECT_EQ(item0Color, selectedColor);
	// Can't test border color, not even by setting objectName

	srv->enterKey(catListItemPath, Qt::Key_Down, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	std::string item1Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, hoverColor);

	srv->enterKey(catListItemPath, Qt::Key_Return, Qt::NoModifier);
	srv->wait(std::chrono::milliseconds(500));
	item1Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_1"), "color");
	EXPECT_EQ(item1Color, selectedColor);

	std::string item2Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_2"), "color");
	EXPECT_EQ(item2Color, defaultColor);

	srv->mouseClick(spix::ItemPath(catListPath + "/listItem_2"));
	srv->wait(std::chrono::milliseconds(500));
	item2Color = srv->getStringProperty(spix::ItemPath(catListPath + "/listItem_2"), "color");
	EXPECT_EQ(item2Color, selectedColor);

	srv->quit();
}

int main(int argc, char* argv[])
{
	// Init Qt Qml Application
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/UI/MainWindow.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	UITestServer server(argc, argv);
	auto bot = new spix::QtQmlBot();
	bot->runTestServer(server);

	app.exec();
	return server.getResult();
}
