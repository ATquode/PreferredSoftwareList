// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
	reuseItems: true
	spacing: 10
	keyNavigationWraps: true

	property color defaultColor: "#EEEEEE"
	property color focusedColor: "#84FFB3"

	Component {
		id: softListDelegate
		Rectangle {
			id: swItemRect
			width: ListView.view.width
			height: childrenRect.height + 10
			color: swItemRect.activeFocus ? focusedColor : defaultColor

			required property var modelData

			Item {
				height: childrenRect.height
				anchors {
					left: parent.left
					leftMargin: 10
					right: parent.right
					rightMargin: 10
					top: parent.top
					topMargin: 5
				}

				ColumnLayout {
					Text {
						text: qsTr(modelData.name)
					}

					RowLayout {
						Repeater {
							model: modelData.categories
							Text {
								text: qsTr(modelData)
							}
						}
					}

					RowLayout {
						Repeater {
							model: modelData.platforms
							Text {
								text: qsTr(modelData)
							}
						}
					}
				}
			}
		}
	}

	delegate: softListDelegate
	ScrollBar.vertical: ScrollBar {}

	model: [
		{
			"name" : "Software 1",
			"categories": ["Category 1"],
			"platforms": ["Windows"]
		},
		{
			"name" : "Software 2",
			"categories": ["Category 1"],
			"platforms": ["macOS"]
		},
		{
			"name" : "Software 3",
			"categories": ["Category 2"],
			"platforms": ["Linux"]
		},
		{
			"name" : "Software 4",
			"categories": ["Category 2"],
			"platforms": ["android", "iOS"]
		}
	]
}
