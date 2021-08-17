// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.h"

#include <QQmlFileSelector>

Application::Application(QGuiApplication& app, QObject* parent)
	: QObject(parent)
{
	qmlRegisterSingletonInstance("SWList.CategoryModel", 1, 0, "CatModel", &modelProvider.categoryModel);
	qmlRegisterSingletonInstance("SWList.SoftwareModel", 1, 0, "SoftModel", &modelProvider.softModel);
	loadQml(engine, app);
}

void Application::loadQml(QQmlApplicationEngine& engine, QGuiApplication& app)
{
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
	QQmlFileSelector* selector = QQmlFileSelector::get(&engine);
	selector->setExtraSelectors(QStringList("mobile"));
#endif /* Q_OS_ANDROID || Q_OS_IOS */
	const QUrl url(QStringLiteral("qrc:/UI/MainWindow.qml"));
	QObject::connect(
		&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject* obj, const QUrl& objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		},
		Qt::QueuedConnection);
	engine.load(url);
}
