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
	return headerData.count();
}

QVariant ContextualRoleTableModel::data(const QModelIndex& index, int role) const
{
	std::pair<Header, QByteArray> headerPair;
	Header header;

	switch (role) {
	case Qt::DisplayRole:
		headerPair = headerData[index.column()];

		if (index.row() == 0) {
			return std::get<1>(headerPair);
		} else {
			header = std::get<0>(headerPair);
			return getSelectedItemIndex(header, index.row());
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

ContextualRole* ContextualRoleTableModel::getContextRole(int row) const
{
	int ctxRoleIndex = row - 1;

	if (ctxRoleIndex < 0) {
		qCritical() << "invalid index";
		return nullptr;
	}

	if (ctxRoleIndex >= ctxRoles.count()) {
		qCritical() << "index out of bounds";
		return nullptr;
	}

	return ctxRoles.at(ctxRoleIndex);
}

void ContextualRoleTableModel::modifyContextRole(Header type, QString value, int row)
{
	ContextualRole* ctxRole = getContextRole(row);
	if (ctxRole == nullptr) {
		return;
	}

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
	case RemoveBtn:
		break;
	}
}

int ContextualRoleTableModel::getSelectedItemIndex(Header type, int row) const
{
	ContextualRole* ctxRole = getContextRole(row);
	if (ctxRole == nullptr) {
		return -1;
	}

	QString value;
	QStringList list;
	switch (type) {
	case Category:
		value = ctxRole->category;
		list = modelProvider->catList();
		break;
	case Platform:
		value = ctxRole->platform;
		list = modelProvider->platModel()->stringList();
		break;
	case PreferenceRole:
		value = ctxRole->prefRole;
		list = modelProvider->preferenceRoleModel()->stringList();
		break;
	case RemoveBtn:
		break;
	}

	return list.indexOf(value);
}
