// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef SOFTWAREITEMPROXYMODEL_H
#define SOFTWAREITEMPROXYMODEL_H

#include <QSortFilterProxyModel>

class SoftwareItemProxyModel : public QSortFilterProxyModel {
	Q_OBJECT
public:
	explicit SoftwareItemProxyModel(QObject* parent = nullptr);

public slots:
	/**
	 * @brief Removes any previous filters from the role and sets the specified filter
	 * @param role The SWItemRole the filter is associated with
	 * @param filter The filter value. Default is "All" - which is equivalent to no filter.
	 */
	void setFilter(int role, QString filter = "All");
	/**
	 * @brief Removes all roles and filters and set the specified values (packed in map)
	 * @param filters Should be a map<String, StringList>, where key should be role value as string, and value should be the associated filter list.
	 */
	void setFilters(QVariant filters);
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
	QHash<int, QStringList> filterPatterns;
};

#endif // SOFTWAREITEMPROXYMODEL_H
