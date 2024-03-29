// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEMPROXYMODEL_H
#define SOFTWAREITEMPROXYMODEL_H

#include "Model/FilterOptionModel.h"

#include <QQmlParserStatus>
#include <QSortFilterProxyModel>
#include <QtQml>

class SoftwareItemProxyModel : public QSortFilterProxyModel, public QQmlParserStatus {
	Q_OBJECT
	Q_INTERFACES(QQmlParserStatus)
	Q_PROPERTY(bool ignoreCategoryFilter MEMBER m_ignoreCategoryFilter)
	Q_PROPERTY(FilterOptionModel* filterProvider MEMBER filterProvider WRITE setFilterProvider)
	QML_NAMED_ELEMENT(SoftProxyModel)
public:
	explicit SoftwareItemProxyModel(QObject* parent = nullptr);

	void setFilterProvider(FilterOptionModel* filterProvider)
	{
		this->filterProvider = filterProvider;
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
		QObject::connect(this->filterProvider, &FilterOptionModel::filtersSet, this, &SoftwareItemProxyModel::setFilters);
		this->filterProvider->onApplied(); // Apply existing filters
#endif /* Q_OS_ANDROID || Q_OS_IOS */
	}

	virtual void classBegin() override;
	virtual void componentComplete() override;

public slots:
	/**
	 * @brief Removes any previous filters from the role and sets the specified filter
	 * @note This does not touch any other roles except the specified one
	 * @param role The SWItemRole the filter is associated with
	 * @param filter The filter value. Default is "All" - which is equivalent to no filter.
	 */
	void setFilter(int role, QString filter = "All");
	/**
	 * @brief Removes all roles and filters and set the specified values
	 * @param filters A map of filters, in role:filterList structure.
	 */
	void setFilters(QHash<int, QStringList> filters);
	/**
	 * @brief Appends filter to the provided role.
	 * If the role already has other filters, the new one just gets appened to its filter list.
	 * @param role The SWItemRole the filter should be associated with
	 * @param filter The filter value
	 */
	void addFilter(int role, QString filter);
	/**
	 * @brief Removes the specified filter from the role. If role has other filters, they are not touched.
	 * @param role The SWItemRole the filter should be removed from
	 * @param filter The filter value
	 */
	void removeFilter(int role, QString filter);

protected:
	/**
	 * @brief Accepts row if all roles has at least one matched filter with the row data.
	 * Which means, within same role, any filter match will be true (OR condition),
	 * but for different roles, all roles have to have a match (AND condition).
	 *
	 * The roles which uses list (e.g. Platform, Category) will check for exact match.
	 * The roles which uses single string will check for substring match.
	 * @param source_row Row index
	 * @param source_parent
	 * @return true if row is accepted, false otherwise
	 */
	bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;

private:
	bool m_ignoreCategoryFilter;
	QHash<int, QStringList> filterPatterns;
	FilterOptionModel* filterProvider;

	QString& removeMnemonicIfExists(QString& filter);
};

#endif // SOFTWAREITEMPROXYMODEL_H
