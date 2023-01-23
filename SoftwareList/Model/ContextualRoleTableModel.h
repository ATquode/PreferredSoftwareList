// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef CONTEXTUALROLETABLEMODEL_H
#define CONTEXTUALROLETABLEMODEL_H

#include "Model/ContextualRole.h"
#include "Model/ModelProvider.h"

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QtQml>

class ContextualRoleTableModel : public QAbstractTableModel, public QQmlParserStatus {
	Q_OBJECT
	Q_INTERFACES(QQmlParserStatus)
	Q_PROPERTY(QVariant contextRoles READ contextRoles WRITE setContextRoles NOTIFY contextRolesChanged)
	Q_PROPERTY(ModelProvider* modelProvider MEMBER modelProvider)
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
	void onCategoryChanged(QString category, int row);
	void onPlatformChanged(QString platform, int row);
	void onPrefRoleChanged(QString prefRole, int row);
	void onAddRowClicked();

private:
	QList<ContextualRole*> ctxRoles;
	ModelProvider* modelProvider;

	enum Header {
		Category,
		Platform,
		PreferenceRole,
		RemoveBtn
	};

	const QList<std::pair<Header, QByteArray>> headerData = {
		{ Category, "Category" },
		{ Platform, "Platform" },
		{ PreferenceRole, "Preference Role" },
		{ RemoveBtn, "" }
	};

	ContextualRole* getContextRole(int row) const;
	void modifyContextRole(Header type, QString value, int row);
	int getSelectedItemIndex(Header type, int row) const;
};

#endif // CONTEXTUALROLETABLEMODEL_H
