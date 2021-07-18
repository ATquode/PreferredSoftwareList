// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick.Controls 2.15

ApplicationWindow {
	width: 640
	height: 480
	visible: true
	title: qsTr("SWList")

	SplitView {
		anchors.fill: parent

		CategoryList {
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
