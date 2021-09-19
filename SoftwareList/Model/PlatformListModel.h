// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef PLATFORMLISTMODEL_H
#define PLATFORMLISTMODEL_H

#include "DB/DBManager.h"

#include <QStringListModel>

class PlatformListModel : public QStringListModel {
	Q_OBJECT
public:
	explicit PlatformListModel(DBManager* dbManager, QObject* parent = nullptr);

private:
	DBManager* dbManager;
};

#endif // PLATFORMLISTMODEL_H
