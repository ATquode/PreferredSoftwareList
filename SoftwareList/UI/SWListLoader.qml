// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15

import "dummy"

Loader {
	source: "SWListModuleImport.qml"
	property var catModel: item != null ? item.catModel : catModelList
	
	CatModelList {
		id: catModelList
	}
}
