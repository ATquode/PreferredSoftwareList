// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include <QQmlFileSelector>

#include "Application.h"

Application::Application(QGuiApplication& app, QObject* parent)
	: QObject(parent)
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
