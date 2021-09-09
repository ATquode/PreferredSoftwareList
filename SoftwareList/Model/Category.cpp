// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

#include "Category.h"

Category::Category(QString name, QMap<int, QString> reqMap)
	: name(name)
	, requirementMap(reqMap)
{
}
