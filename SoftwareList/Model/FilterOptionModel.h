// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef FILTEROPTIONMODEL_H
#define FILTEROPTIONMODEL_H

#include "Model/SWItemRole.h"

#include <QAbstractListModel>

class FilterOptionState : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString filter READ getFilter CONSTANT)
	Q_PROPERTY(bool isSelected MEMBER selected)
public:
	bool selected;

	FilterOptionState(QString filter, bool selected = false, QObject* parent = nullptr)
		: QObject(parent)
		, selected(selected)
		, filter(filter)
	{
	}

	QString getFilter()
	{
		return filter;
	}

private:
	QString filter;
};

class FilterTypeOption {
public:
	int itemRole;
	QString type;
	QList<FilterOptionState*> options;

	FilterTypeOption(int itemRole, QString type, QList<FilterOptionState*> options)
		: itemRole(itemRole)
		, type(type)
		, options(options)
	{
	}
};

class FilterOptionModel : public QAbstractListModel {
	Q_OBJECT

public:
	explicit FilterOptionModel(QStringList platforms, QObject* parent = nullptr);

	// Basic functionality:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

signals:
	void filtersSet(QHash<int, QStringList> filters);

public slots:
	void onApplied();
	void onCancelled();

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	QList<FilterTypeOption> currentFilterList;
	QList<FilterTypeOption> activeFilterList;

	const QHash<int, QByteArray> itemRoleString = {
		{ SWItemRole::PlatformRole, "Platform" }
	};

	const QHash<int, QByteArray> roles = {
		{ SWItemRole::FilterItemRole, "filterItemRole" },
		{ SWItemRole::TypeRole, "filterType" },
		{ SWItemRole::OptionRole, "filterOptions" }
	};

	QList<FilterTypeOption> deepCopy(QList<FilterTypeOption>& filterList);
};

#endif // FILTEROPTIONMODEL_H
