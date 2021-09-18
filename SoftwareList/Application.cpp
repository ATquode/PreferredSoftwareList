// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.h"
#include "Model/SoftwareItemProxyModel.h"

#include <QQmlFileSelector>

Application::Application(QGuiApplication& app, QObject* parent)
	: QObject(parent)
	, modelProvider(&dbManager)
{
	registerCppTypesToQml();
	loadQml(engine, app);

	QObject* rootObj = engine.rootObjects().constFirst();
	setupSlots(rootObj);
}

void Application::registerCppTypesToQml()
{
	qmlRegisterUncreatableType<SWItemRole>("SWList", 1, 0, "SWItemRole", "Enum wrapper not creatable");
	qmlRegisterSingletonInstance("SWList", 1, 0, "ModelProvider", &modelProvider);
	qmlRegisterType<SoftwareItemProxyModel>("SWList", 1, 0, "SoftProxyModel");
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

void Application::setupSlots(QObject* rootObj)
{
	auto proxyModels = rootObj->findChildren<SoftwareItemProxyModel*>();
	for (auto proxyModel : qAsConst(proxyModels)) {
		// clang-format off
		QObject::connect(rootObj, SIGNAL(setFilter(int,QString)), proxyModel, SLOT(setFilter(int,QString)));
		// clang-format on
	}
}
