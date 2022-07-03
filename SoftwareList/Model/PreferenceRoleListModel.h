// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef PREFERENCEROLELISTMODEL_H
#define PREFERENCEROLELISTMODEL_H

#include "DB/DBManager.h"

#include <QStringListModel>

class PreferenceRoleListModel : public QStringListModel {
	Q_OBJECT
public:
	explicit PreferenceRoleListModel(DBManager* dbManager, QObject* parent = nullptr);

private:
	DBManager* dbManager;
};

#endif // PREFERENCEROLELISTMODEL_H
