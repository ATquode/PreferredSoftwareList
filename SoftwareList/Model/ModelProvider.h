// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#ifndef MODELPROVIDER_H
#define MODELPROVIDER_H

#include "Model/CategoryModel.h"

class ModelProvider : public QObject {
public:
	explicit ModelProvider(QObject* parent = nullptr);

	CategoryModel categoryModel;
};

#endif // MODELPROVIDER_H
