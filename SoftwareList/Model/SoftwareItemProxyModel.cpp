// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItemProxyModel.h"
#include "Model/SWItemRole.h"

#include <QDebug>
#include <QUrl>

SoftwareItemProxyModel::SoftwareItemProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{
}

void SoftwareItemProxyModel::setFilter(int role, QString filter)
{
	if (filter == "All") {
		filterPatterns.remove(role);
	} else {
		filterPatterns[role] = QStringList(filter);
	}
	invalidateFilter();
}

void SoftwareItemProxyModel::setFilters(QVariant filters)
{
	QVariantMap filterMap = filters.toMap();
	QHash<int, QStringList> filterHash;
	for (auto it = filterMap.keyValueBegin(), end = filterMap.keyValueEnd(); it != end; ++it) {
		bool ok;
		int key = it->first.toInt(&ok);
		if (!ok) {
			continue;
		}
		QStringList value = it->second.toStringList();
		if (value.isEmpty()) {
			return;
		}
		filterHash[key] = value;
	}
	filterPatterns = filterHash;
	invalidateFilter();
}

void SoftwareItemProxyModel::addFilter(int role, QString filter)
{
	if (filterPatterns.contains(role)) {
		filterPatterns[role].append(filter);
	} else {
		filterPatterns[role] = QStringList(filter);
	}
	invalidateFilter();
}

void SoftwareItemProxyModel::removeFilter(int role, QString filter)
{
	filterPatterns[role].removeAll(filter);
	if (filterPatterns[role].size() == 0) {
		filterPatterns.remove(role);
	}
	invalidateFilter();
}

bool SoftwareItemProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
	for (auto it = filterPatterns.keyBegin(), end = filterPatterns.keyEnd(); it != end; ++it) {
		if (filterPatterns[*it].isEmpty()) {
			qCritical() << "Empty filter list for role exists in filterPatterns - this is not allowed. Rejecting filtering. Role: " << *it;
			return false;
		}

		QVariant dataVar = sourceModel()->data(index, *it);
		QStringList dataList;
		QString dataStr;
		switch (*it) {
		case SWItemRole::CategoryRole:
		case SWItemRole::PlatformRole:
			dataList = dataVar.toStringList();
			break;
		case SWItemRole::NameRole:
		case SWItemRole::LimitationRole:
		case SWItemRole::NotesRole:
			dataStr = dataVar.toString();
			break;
		case SWItemRole::UrlRole:
			dataStr = dataVar.toUrl().toString();
			break;
		}
		bool matched = false;
		for (const QString& filter : filterPatterns[*it]) {
			if (!dataList.isEmpty()) {
				for (const QString& dataString : qAsConst(dataList)) {
					if (dataString == filter) {
						matched = true;
						break;
					}
				}
			} else if (!dataStr.isEmpty()) {
				if (dataStr.contains(filter)) {
					matched = true;
					break;
				}
			} else {
				qCritical() << "Both dataList & dataStr is empty. Rejecting filtering. Role: " << *it << ", Filter value: " << dataVar;
				return false;
			}
			if (matched) {
				break; // match for any filter within a role. This is the OR condition. Check the next role.
			}
		}
		if (!matched) {
			return false; // no match for a whole role, reject. This is the AND condition.
		}
	}
	return true;
}
