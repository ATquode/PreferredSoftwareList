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
	return headerData.count() + 1;
}

QVariant ContextualRoleTableModel::data(const QModelIndex& index, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		if (index.row() == 0) {
			if (index.column() < headerData.count()) {
				return headerData[index.column()];
			} else {
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
	ctxRoles.append(new ContextualRole("", "", ""));

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
	QObject::connect(swEntryWindow, SIGNAL(categoryChanged(QString,int)), this, SLOT(onCategoryChanged(QString,int)));
	QObject::connect(swEntryWindow, SIGNAL(platformChanged(QString,int)), this, SLOT(onPlatformChanged(QString,int)));
	QObject::connect(swEntryWindow, SIGNAL(prefRoleChanged(QString,int)), this, SLOT(onPrefRoleChanged(QString,int)));
	QObject::connect(swEntryWindow, SIGNAL(addRowClicked()), this, SLOT(onAddRowClicked()));
	// clang-format on
}

void ContextualRoleTableModel::onCategoryChanged(QString category, int row)
{
	modifyContextRole(Header::Category, category, row);
}

void ContextualRoleTableModel::onPlatformChanged(QString platform, int row)
{
	modifyContextRole(Header::Platform, platform, row);
}

void ContextualRoleTableModel::onPrefRoleChanged(QString prefRole, int row)
{
	modifyContextRole(Header::PreferenceRole, prefRole, row);
}

void ContextualRoleTableModel::onAddRowClicked()
{
	ContextualRole* ctxRole = new ContextualRole("", "", "");
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	ctxRoles.append(ctxRole);
	endInsertRows();
}

void ContextualRoleTableModel::modifyContextRole(Header type, QString value, int row)
{
	int ctxRoleIndex = row - 1;

	if (ctxRoleIndex < 0) {
		qCritical() << "invalid index";
		return;
	}

	if (ctxRoleIndex >= ctxRoles.count()) {
		qCritical() << "index out of bounds";
		return;
	}

	ContextualRole* ctxRole = ctxRoles.at(ctxRoleIndex);

	switch (type) {
	case Category:
		if (ctxRole->category == value) {
			return;
		}
		ctxRole->category = value;
		break;
	case Platform:
		if (ctxRole->platform == value) {
			return;
		}
		ctxRole->platform = value;
		break;
	case PreferenceRole:
		if (ctxRole->prefRole == value) {
			return;
		}
		ctxRole->prefRole = value;
		break;
	}
}
