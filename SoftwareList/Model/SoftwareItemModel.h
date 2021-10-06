// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEMMODEL_H
#define SOFTWAREITEMMODEL_H

#include "DB/DBManager.h"
#include "Model/SWItemRole.h"
#include "Model/SoftwareItem.h"

#include <QAbstractListModel>

class SoftwareItemModel : public QAbstractListModel {
	Q_OBJECT
public:
	explicit SoftwareItemModel(DBManager* dbManager, QObject* parent = nullptr);
	void addItem(const SoftwareItem& item);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	QList<SoftwareItem> items;
	DBManager* dbManager;

	const QHash<int, QByteArray> roles = {
		{ SWItemRole::NameRole, "name" },
		{ SWItemRole::CategoryRole, "categories" },
		{ SWItemRole::PlatformRole, "platforms" },
		{ SWItemRole::PreferenceRole, "prefRoles" },
		{ SWItemRole::LimitationRole, "limitation" },
		{ SWItemRole::UrlRole, "url" },
		{ SWItemRole::NotesRole, "notes" }
	};
};

#endif // SOFTWAREITEMMODEL_H
