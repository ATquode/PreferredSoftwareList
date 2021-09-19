// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "FilterOptionModel.h"

FilterOptionModel::FilterOptionModel(QStringList platforms, QObject* parent)
	: QAbstractListModel(parent)
{
	QList<FilterOptionState*> platformOptions;
	for (QString& platform : platforms) {
		platformOptions.append(new FilterOptionState(platform));
	}
	FilterTypeOption platformFilters(SWItemRole::PlatformRole, itemRoleString[SWItemRole::PlatformRole], platformOptions);
	currentFilterList.append(platformFilters);
	activeFilterList = deepCopy(currentFilterList);
}

int FilterOptionModel::rowCount(const QModelIndex& parent) const
{
	// For list models only the root node (an invalid parent) should return the list's size. For all
	// other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
	if (parent.isValid())
		return 0;

	return currentFilterList.count();
}

QVariant FilterOptionModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	const FilterTypeOption& filterTypeOption = currentFilterList[index.row()];
	switch (role) {
	case SWItemRole::FilterItemRole:
		return filterTypeOption.itemRole;
	case SWItemRole::TypeRole:
		return filterTypeOption.type;
	case SWItemRole::OptionRole:
		return QVariant::fromValue(filterTypeOption.options);
	default:
		return QVariant();
	}
}

void FilterOptionModel::onApplied()
{
	activeFilterList = deepCopy(currentFilterList);
	QHash<int, QStringList> activeFilterPatterns;
	for (FilterTypeOption& fOpt : activeFilterList) {
		QStringList activeFilters;
		for (FilterOptionState* fState : qAsConst(fOpt.options)) {
			if (fState->selected) {
				activeFilters.append(fState->getFilter());
			}
		}
		if (!activeFilters.isEmpty()) {
			activeFilterPatterns[fOpt.itemRole] = activeFilters;
		}
	}
	emit filtersSet(activeFilterPatterns);
}

void FilterOptionModel::onCancelled()
{
	beginResetModel();
	currentFilterList = deepCopy(activeFilterList);
	endResetModel();
}

QHash<int, QByteArray> FilterOptionModel::roleNames() const
{
	return roles;
}

QList<FilterTypeOption> FilterOptionModel::deepCopy(QList<FilterTypeOption>& filterList)
{
	QList<FilterTypeOption> newFilterList;
	for (FilterTypeOption& fOpt : filterList) {
		QList<FilterOptionState*> newOptStateList;
		for (FilterOptionState* optState : qAsConst(fOpt.options)) {
			newOptStateList.append(new FilterOptionState(optState->getFilter(), optState->selected));
		}
		newFilterList.append(FilterTypeOption(fOpt.itemRole, fOpt.type, newOptStateList));
	}
	return newFilterList;
}
