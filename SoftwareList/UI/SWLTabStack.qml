// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick.Layouts 1.15

StackLayout {
	anchors.fill: parent

	CategoryList {
		activeFocusOnTab: true
		selectedIndex: -1
		currentIndex: -1
		isMobile: true
		model: moduleLoader.catModel
		onItemSelected: currentIndex = -1;
	}

	SoftwareList {
		activeFocusOnTab: true
		model: moduleLoader.softModel
	}
	
	SWListLoader {
		id: moduleLoader
	}
}
