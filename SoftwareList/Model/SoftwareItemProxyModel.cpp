// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "SoftwareItemProxyModel.h"
#include "Model/SWItemRole.h"
#include "Model/SoftwareItem.h"

#include <QDebug>
#include <QQmlApplicationEngine>
#include <QUrl>

SoftwareItemProxyModel::SoftwareItemProxyModel(QObject* parent)
	: QSortFilterProxyModel(parent)
{
	m_ignoreCategoryFilter = false;
}

void SoftwareItemProxyModel::classBegin()
{
	QQmlApplicationEngine* engine = qobject_cast<QQmlApplicationEngine*>(qmlEngine(this));
	if (!engine) {
		qCritical() << "engine is null";
		return;
	}

	auto rootObjs = engine->rootObjects();
	if (rootObjs.isEmpty()) {
		return;
	}
	QObject* rootObj = rootObjs.constFirst();
	// clang-format off
	QObject::connect(rootObj, SIGNAL(setFilter(int,QString)), this, SLOT(setFilter(int,QString)));
#if !defined (Q_OS_ANDROID) && !defined (Q_OS_IOS)
	QObject::connect(rootObj, SIGNAL(addFilter(int,QString)), this, SLOT(addFilter(int,QString)));
	QObject::connect(rootObj, SIGNAL(removeFilter(int,QString)), this, SLOT(removeFilter(int,QString)));
#endif /* NOT Q_OS_ANDROID && NOT Q_OS_IOS */
	// clang-format on
}

void SoftwareItemProxyModel::componentComplete()
{
}

void SoftwareItemProxyModel::setFilter(int role, QString filter)
{
	if (m_ignoreCategoryFilter && role == SWItemRole::CategoryRole) {
		return;
	}
	if (filter == "All") {
		filterPatterns.remove(role);
	} else {
		filterPatterns[role] = QStringList(filter);
	}
	invalidateFilter();
}

void SoftwareItemProxyModel::setFilters(QHash<int, QStringList> filters)
{
	if (!m_ignoreCategoryFilter && filterPatterns.contains(SWItemRole::CategoryRole)) {
		filters[SWItemRole::CategoryRole] = filterPatterns[SWItemRole::CategoryRole];
	}
	filterPatterns = filters;
	invalidateFilter();
}

void SoftwareItemProxyModel::addFilter(int role, QString filter)
{
	filter = removeMnemonicIfExists(filter);
	if (filterPatterns.contains(role)) {
		filterPatterns[role].append(filter);
	} else {
		filterPatterns[role] = QStringList(filter);
	}
	invalidateFilter();
}

void SoftwareItemProxyModel::removeFilter(int role, QString filter)
{
	filter = removeMnemonicIfExists(filter);
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
				if (*it == SWItemRole::PreferenceRole) {
					auto prefList = dataVar.value<QList<ContextualRole*>>();
					for (const ContextualRole* ctxRole : qAsConst(prefList)) {
						if (ctxRole->prefRole == filter) {
							bool categoryMatch = false;
							if (filterPatterns.contains(SWItemRole::CategoryRole)) {
								for (const QString& category : filterPatterns[SWItemRole::CategoryRole]) {
									if (ctxRole->category == category) {
										categoryMatch = true;
										break;
									}
								}
							} else {
								categoryMatch = true;
							}

							bool platformMatch = false;
							if (filterPatterns.contains(SWItemRole::PlatformRole)) {
								for (const QString& platform : filterPatterns[SWItemRole::PlatformRole]) {
									if (ctxRole->platform == platform) {
										platformMatch = true;
										break;
									}
								}
							} else {
								platformMatch = true;
							}

							if (categoryMatch && platformMatch) {
								matched = true;
								break;
							}
						}
					}
				} else {
					qCritical() << "Both dataList & dataStr is empty. Rejecting filtering. Role: " << *it << ", Filter value: " << dataVar;
					return false;
				}
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

QString& SoftwareItemProxyModel::removeMnemonicIfExists(QString& filter)
{
	int index = filter.indexOf('&');
	if (index == -1 || index == filter.size() - 1 || filter.at(index + 1) == ' ') {
		return filter;
	}
	return filter.remove(index, 1);
}
