// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Model/ModelProvider.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

class Application : public QObject {
	Q_OBJECT
public:
	explicit Application(QGuiApplication& app, QObject* parent = nullptr);

private:
	void registerCppTypesToQml();
	void loadQml(QQmlApplicationEngine& engine, QGuiApplication& app);
	void setupSlots(QObject* rootObj);

	QQmlApplicationEngine engine;
	DBManager dbManager;
	ModelProvider modelProvider;
};

#endif // APPLICATION_H
