// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItemModel.h"

SoftwareItemModel::SoftwareItemModel(DBManager* dbManager, QObject* parent)
	: QAbstractListModel(parent)
{
	this->dbManager = dbManager;
	SoftwareItem item1("Software 1", QStringList("Category 1"), QStringList("Windows"), "limitation 1", QUrl(), "");
	SoftwareItem item2("Software 2", QStringList("Category 1"), QStringList({ "macOS", "iOS" }), "limitation 2", QUrl(), "note 2");
	SoftwareItem item3("Software 3", QStringList("Category 2"), QStringList("Linux"), "", QUrl(), "");
	SoftwareItem item4("Software 4", QStringList("Category 2"), QStringList({ "android", "iOS" }), "", QUrl(), "note 4");
	items << item1 << item2 << item3 << item4;
}

void SoftwareItemModel::addItem(const SoftwareItem& item)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	items << item;
	endInsertRows();
}

QVariant SoftwareItemModel::data(const QModelIndex& index, int role) const
{
	if (index.row() < 0 || index.row() >= items.count()) {
		return QVariant();
	}

	const SoftwareItem& item = items[index.row()];
	switch (role) {
	case SWItemRole::NameRole:
		return item.name;
	case SWItemRole::CategoryRole:
		return item.categories;
	case SWItemRole::PlatformRole:
		return item.platforms;
	case SWItemRole::LimitationRole:
		return item.limitation;
	case SWItemRole::UrlRole:
		return item.url;
	case SWItemRole::NotesRole:
		return item.notes;
	default:
		return QVariant();
	}
}

int SoftwareItemModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return items.count();
}

QHash<int, QByteArray> SoftwareItemModel::roleNames() const
{
	return roles;
}
