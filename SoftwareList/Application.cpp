// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Application.h"
#include "Model/ContextualRoleTableModel.h"
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
	qmlRegisterType<SoftwareItem>("SWList", 1, 0, "SoftwareItem");
	qmlRegisterType<ContextualRoleTableModel>("SWList", 1, 0, "ContextualRoleTableModel");
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
#if defined (Q_OS_ANDROID) || defined (Q_OS_IOS)
		QObject::connect(modelProvider.filterOptionsModel(), &FilterOptionModel::filtersSet, proxyModel, &SoftwareItemProxyModel::setFilters);
#else
		QObject::connect(rootObj, SIGNAL(addFilter(int,QString)), proxyModel, SLOT(addFilter(int,QString)));
		QObject::connect(rootObj, SIGNAL(removeFilter(int,QString)), proxyModel, SLOT(removeFilter(int,QString)));
#endif /* Q_OS_ANDROID || Q_OS_IOS */
	}
	
#if defined (Q_OS_ANDROID) || defined (Q_OS_IOS)
	QObject::connect(rootObj, SIGNAL(applyFiltering()), modelProvider.filterOptionsModel(), SLOT(onApplied()));
	QObject::connect(rootObj, SIGNAL(cancelFiltering()), modelProvider.filterOptionsModel(), SLOT(onCancelled()));
#endif /* Q_OS_ANDROID || Q_OS_IOS */
	// clang-format on
}
