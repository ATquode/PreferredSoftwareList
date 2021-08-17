// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15

ListModel {
	ListElement {
		name: "Software 1"
		categories: [
			ListElement {
				modelData: "Category 1"
			}
		]
		platforms: [
			ListElement {
				modelData: "Windows"
			}
		]
		limitation: ""
		url: ""
		notes: ""
	}
	ListElement {
		name: "Software 2"
		categories: [
			ListElement {
				modelData: "Category 1"
			}
		]
		platforms: [
			ListElement {
				modelData: "macOS"
			}
		]
		limitation: ""
		url: ""
		notes: ""
	}
	ListElement {
		name: "Software 3"
		categories: [
			ListElement {
				modelData: "Category 2"
			}
		]
		platforms: [
			ListElement {
				modelData: "Linux"
			}
		]
		limitation: ""
		url: ""
		notes: ""
	}
	ListElement {
		name: "Software 4"
		categories: [
			ListElement {
				modelData: "Category 2"
			}
		]
		platforms: [
			ListElement {
				modelData: "android"
			},
			ListElement {
				modelData: "iOS"
			}
		]
		limitation: ""
		url: ""
		notes: ""
	}
}
