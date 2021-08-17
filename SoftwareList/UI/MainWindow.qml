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
	
	SWListLoader {
		id: moduleLoader
	}

	SplitView {
		objectName: "splitView"
		anchors.fill: parent

		CategoryList {
			id: catList
			SplitView.preferredWidth: parent.width / 5
			KeyNavigation.right: softList
			activeFocusOnTab: true
			model: moduleLoader.catModel
			onItemSelected: {
				selectedIndex = index;
				currentIndex = index;
				catList.forceActiveFocus();
			}
		}

		SoftwareList {
			id: softList
			KeyNavigation.left: catList
			activeFocusOnTab: true
			model: moduleLoader.softModel
		}
	}
}
