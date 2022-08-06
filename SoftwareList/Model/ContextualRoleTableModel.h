// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CONTEXTUALROLETABLEMODEL_H
#define CONTEXTUALROLETABLEMODEL_H

#include "Model/ContextualRole.h"

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QtQml>

class ContextualRoleTableModel : public QAbstractTableModel, public QQmlParserStatus {
	Q_OBJECT
	Q_INTERFACES(QQmlParserStatus)
	Q_PROPERTY(QVariant contextRoles READ contextRoles WRITE setContextRoles NOTIFY contextRolesChanged)
	QML_ELEMENT

public:
	explicit ContextualRoleTableModel(QObject* parent = nullptr);

	QVariant contextRoles()
	{
		return QVariant::fromValue(ctxRoles);
	}

	void setContextRoles(QVariant ctxRoles)
	{
		this->ctxRoles = ctxRoles.value<QList<ContextualRole*>>();
	}

	int rowCount(const QModelIndex& = QModelIndex()) const override;
	int columnCount(const QModelIndex& = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;

	virtual void classBegin() override;
	virtual void componentComplete() override;

signals:
	void contextRolesChanged();

public slots:
	void onCategoryChanged(int catIndex, int row);

private:
	QList<ContextualRole*> ctxRoles;

	enum Header {
		Category,
		Platform,
		PreferenceRole
	};

	const QHash<int, QByteArray> headerData = {
		{ Category, "Category" },
		{ Platform, "Platform" },
		{ PreferenceRole, "Preference Role" }
	};
};

#endif // CONTEXTUALROLETABLEMODEL_H
