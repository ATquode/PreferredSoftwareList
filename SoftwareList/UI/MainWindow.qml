// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

import SWList 1.0

ApplicationWindow {
	objectName: "mainWindow"
	width: 640
	height: 480
	visible: true
	title: qsTr("SWList")
	
	signal setFilter(int role, string filter)
	signal addFilter(int role, string filter)
	signal removeFilter(int role, string filter)

	menuBar: SWLMenuBar {
//	SWLMenuBar{
		onMenuPressed: {
			if (menuType === SWLMenuBar.MenuType.NewSoftware) {
				var comp = Qt.createComponent("SoftwareEntry.qml");
				var window = comp.createObject(this);
				window.show();
			}
		}

		onMenuToggled: {
			if (isChecked) {
				addFilter(menuType, menuValue);
			} else {
				removeFilter(menuType, menuValue);
			}
		}
	}

	SplitView {
		objectName: "splitView"
		anchors.fill: parent

		CategoryList {
			id: catList
			SplitView.preferredWidth: parent.width / 5
			KeyNavigation.right: softList
			activeFocusOnTab: true
			model: ModelProvider.catModel
			onItemSelected: {
				selectedIndex = index;
				currentIndex = index;
				catList.forceActiveFocus();
				setFilter(SWItemRole.CategoryRole, category);
			}
		}

		SoftwareList {
			id: softList
			KeyNavigation.left: catList
			activeFocusOnTab: true
			model: SoftProxyModel {
				sourceModel: ModelProvider.softSrcModel
			}
		}
	}
}
