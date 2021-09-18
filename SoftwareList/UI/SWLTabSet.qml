// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

import SWList 1.0

SwipeView {
	anchors.fill: parent
	
	signal navigateToNewPage(string newTitle, Component newPage)
	signal categoryFilterSet(string category)

	CategoryList {
		activeFocusOnTab: true
		selectedIndex: -1
		currentIndex: -1
		isMobile: true
		model: ModelProvider.catModel
		onItemSelected: {
			navigateToNewPage(category, singleCategorySoftList);
			categoryFilterSet(category);
			currentIndex = -1;
		}
	}

	SoftwareList {
		activeFocusOnTab: true
		model: SoftProxyModel {
			sourceModel: ModelProvider.softSrcModel
			ignoreCategoryFilter: true
		}
	}
	
	Component {
		id: singleCategorySoftList
		SoftwareList {
			model: SoftProxyModel {
				sourceModel: ModelProvider.softSrcModel
			}
		}
	}
}
