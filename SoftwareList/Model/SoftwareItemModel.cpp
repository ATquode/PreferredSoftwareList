// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItemModel.h"

SoftwareItemModel::SoftwareItemModel(DBManager* dbManager, QObject* parent)
	: QAbstractListModel(parent)
{
	this->dbManager = dbManager;
	if (dbManager != nullptr) {
		addItem(new SoftwareItem("Software 1", QStringList("Category 1"), QStringList("Windows"),
			QList<ContextualRole*>({ new ContextualRole("Category 1", "Windows", "Main") }), "limitation 1", QUrl(), ""));
		addItem(new SoftwareItem("Software 2", QStringList("Category 1"), QStringList({ "macOS", "iOS" }),
			QList<ContextualRole*>({ new ContextualRole("Category 1", "macOS", "Secondary"),
				new ContextualRole("Category 1", "iOS", "Fallback") }),
			"limitation 2", QUrl(), "note 2"));
		addItem(new SoftwareItem("Software 3", QStringList("Category 2"), QStringList("Linux"),
			QList<ContextualRole*>({ new ContextualRole("Category 2", "Linux", "Primary") }), "", QUrl(), ""));
		addItem(new SoftwareItem("Software 4", QStringList("Category 2"), QStringList({ "android", "iOS" }),
			QList<ContextualRole*>({ new ContextualRole("Category 2", "android", "Tertiary"),
				new ContextualRole("Category 2", "iOS", "Inactive") }),
			"", QUrl(), "note 4"));
	}
}

void SoftwareItemModel::addItem(const SoftwareItem* item)
{
	if (dbManager != nullptr) {
		QVariant id = dbManager->addSoftwareItem(item);
		if (!id.isValid()) {
			qCritical() << "Failed to insert Software item: " << item->name;
			return;
		}
		bool ok;
		int softwareID = id.toInt(&ok);
		if (!ok) {
			qCritical() << "Failed to convert Software ID to int for Software item: " << item->name;
			return;
		}

		for (const QString& category : item->categories) {
			id = dbManager->getCategoryID(category);
			if (id.isValid()) {
				int categoryID = id.toInt();
				id = dbManager->addSoftwareCategoryLink(softwareID, categoryID);
				if (!id.isValid()) {
					qCritical() << "Failed to link Sofware item: " << item->name << " with Category: " << category;
					// TODO: Rollback
				}
			} else {
				qCritical() << "Category: " << category << " does not exist in DB";
			}
		}

		for (const QString& platform : item->platforms) {
			id = dbManager->getPlatformID(platform);
			if (id.isValid()) {
				int platformID = id.toInt();
				id = dbManager->addSoftwarePlatformLink(softwareID, platformID);
				if (!id.isValid()) {
					qCritical() << "Failed to link Software item: " << item->name << " with Platform: " << platform;
					// TODO: Rollback
				}
			} else {
				qCritical() << "Platform: " << platform << " does not exist in DB";
			}
		}

		for (const ContextualRole* prefRole : item->preferenceRoles) {
			id = dbManager->getCategoryID(prefRole->category);
			if (!id.isValid()) {
				qCritical() << "Category: " << prefRole->category << " does not exist in DB";
				continue;
			}
			int categoryID = id.toInt();

			id = dbManager->getPlatformID(prefRole->platform);
			if (!id.isValid()) {
				qCritical() << "Platform: " << prefRole->platform << " does not exist in DB";
				continue;
			}
			int platformID = id.toInt();

			id = dbManager->getPreferenceRoleID(prefRole->prefRole);
			if (!id.isValid()) {
				qCritical() << "Preference Role: " << prefRole->prefRole << " does not exist in DB";
				continue;
			}
			int prefRoleID = id.toInt();

			id = dbManager->addCategoryPlatformSoftwareRoleLink(categoryID, platformID, softwareID, prefRoleID);
			if (!id.isValid()) {
				qCritical() << "Failed to link Software item: " << item->name << " with Preference Role: " << prefRole->prefRole << " with Category: " << prefRole->category << " with Platfrom: " << prefRole->platform;
				// TODO: Rollback
			}
		}
	}

	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	items << item;
	endInsertRows();
}

QVariant SoftwareItemModel::data(const QModelIndex& index, int role) const
{
	if (index.row() < 0 || index.row() >= items.count()) {
		return QVariant();
	}

	const SoftwareItem* item = items[index.row()];
	switch (role) {
	case SWItemRole::NameRole:
		return item->name;
	case SWItemRole::CategoryRole:
		return item->categories;
	case SWItemRole::PlatformRole:
		return item->platforms;
	case SWItemRole::PreferenceRole:
		return QVariant::fromValue(item->preferenceRoles);
	case SWItemRole::LimitationRole:
		return item->limitation;
	case SWItemRole::UrlRole:
		return item->url;
	case SWItemRole::NotesRole:
		return item->notes;
	default:
		return QVariant();
	}
}

int SoftwareItemModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return items.count();
}

bool SoftwareItemModel::onEntryDone(SoftwareItem* item, int itemID)
{
	if (itemID == -1) {
		qDebug() << item->name;
	}
	return true;
}

QHash<int, QByteArray> SoftwareItemModel::roleNames() const
{
	return roles;
}
