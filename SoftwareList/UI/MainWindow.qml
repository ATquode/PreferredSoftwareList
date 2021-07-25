// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
	objectName: "mainWindow"
	width: 640
	height: 480
	visible: true
	title: qsTr("SWList")

	SplitView {
		objectName: "splitView"
		anchors.fill: parent

		CategoryList {
			objectName: "categoryList"
			SplitView.preferredWidth: parent.width / 5
			model: ['Category 1', 'Category 2', 'Category 3']
			onItemSelected: {
				selectedIndex = index;
				currentIndex = index;
			}
		}

		SoftwareList {}
	}
}
