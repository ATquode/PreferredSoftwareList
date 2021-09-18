// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

import SWList 1.0

import ".."

ApplicationWindow {
	visible: true
	title: qsTr("SWList")
	
	signal setFilter(int role, string filter)
	
	header: SWLToolBar {
		id: headerToolbar
		pageTitle: title
		
		onBackBtnClicked: {
			navStack.pop();
			backBtnVisible = navStack.depth > 1;
			if (!backBtnVisible) {
				pageTitle = title;
			}
		}
	}

	StackView {
		id: navStack
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
				
				onNavigateToNewPage: {
					navStack.push(newPage);
					headerToolbar.pageTitle = newTitle;
					headerToolbar.backBtnVisible = true;
				}
				
				onCategoryFilterSet: setFilter(SWItemRole.CategoryRole, category)
			}
		}
	}
}
