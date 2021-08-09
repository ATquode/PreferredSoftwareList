// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15

ListModel {
	ListElement {
		name: "Software 1"
		categories: [
			ListElement {
				display: "Category 1"
			}
		]
		platforms: [
			ListElement {
				display: "Windows"
			}
		]
	}
	ListElement {
		name: "Software 2"
		categories: [
			ListElement {
				display: "Category 1"
			}
		]
		platforms: [
			ListElement {
				display: "macOS"
			}
		]
	}
	ListElement {
		name: "Software 3"
		categories: [
			ListElement {
				display: "Category 2"
			}
		]
		platforms: [
			ListElement {
				display: "Linux"
			}
		]
	}
	ListElement {
		name: "Software 4"
		categories: [
			ListElement {
				display: "Category 2"
			}
		]
		platforms: [
			ListElement {
				display: "android"
			},
			ListElement {
				display: "iOS"
			}
		]
	}
}
