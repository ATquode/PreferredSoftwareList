// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

import ".."

ApplicationWindow {
	visible: true
	title: qsTr("SWList")

	StackView {
		anchors.fill: parent
		initialItem: tabBarContainer
		focus: true
	}

	Component {
		id: tabBarContainer
		Page {
			footer: SWLTabBar {
				id: tabBar
				currentIndex: tabSet.currentIndex
			}

			SWLTabSet {
				id: tabSet
				currentIndex: tabBar.currentIndex
			}
		}
	}
}
