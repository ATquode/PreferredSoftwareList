// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "ContextualRoleTableModel.h"

#include <QQuickWindow>

ContextualRoleTableModel::ContextualRoleTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
}

int ContextualRoleTableModel::rowCount(const QModelIndex&) const
{
	int dataCount = ctxRoles.count() > 0 ? ctxRoles.count() : 1;
	return dataCount + 1;
}

int ContextualRoleTableModel::columnCount(const QModelIndex&) const
{
	return 3 + 1;
}

QVariant ContextualRoleTableModel::data(const QModelIndex& index, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (index.row() == 0) {
			switch (index.column()) {
			case 0:
				return "Category";
			case 1:
				return "Platform";
			case 2:
				return "Preference Role";
			default:
				return "";
			}
		} else {
			return -1;
		}
	default:
		break;
	}
	return QVariant();
}

void ContextualRoleTableModel::classBegin()
{
}

void ContextualRoleTableModel::componentComplete()
{
	QQmlApplicationEngine* engine = qobject_cast<QQmlApplicationEngine*>(qmlEngine(this));
	if (!engine) {
		qCritical() << "engine is null";
		return;
	}

	auto rootObjs = engine->rootObjects();
	if (rootObjs.isEmpty()) {
		qCritical() << "root obj is empty";
		return;
	}
	QObject* rootObj = rootObjs.constFirst();
	auto swEntryWindow = rootObj->findChild<QQuickWindow*>("softwareEntryWindow");
	if (!swEntryWindow) {
		qCritical() << "swEntryWindow is null";
		return;
	}

	// clang-format off
	QObject::connect(swEntryWindow, SIGNAL(categoryChanged(int,int)), this, SLOT(onCategoryChanged(int,int)));
	// clang-format on
}

void ContextualRoleTableModel::onCategoryChanged(int catIndex, int row)
{
	int ctxRoleIndex = row - 1;
}
