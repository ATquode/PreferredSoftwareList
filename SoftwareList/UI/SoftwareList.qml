// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "dummy"

ListView {
	reuseItems: true
	spacing: 10
	keyNavigationWraps: true
	model: SoftModelList {}

	property color defaultColor: "#EEEEEE"
	property color focusedColor: "#84FFB3"

	Component {
		id: softListDelegate
		Rectangle {
			id: swItemRect
			objectName: "listItem_" + index
			width: ListView.view.width
			height: childrenRect.height + 10
			color: swItemRect.activeFocus ? focusedColor : defaultColor

			required property int index
			required property string name
			required property var categories
			required property var platforms
			required property var prefRoles
			required property string limitation
			required property url url
			required property string notes

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
						text: qsTr(name)
					}

					RowLayout {
						Repeater {
							model: categories
							Text {
								text: qsTr(modelData)
							}
						}
					}

					RowLayout {
						Repeater {
							model: platforms
							Text {
								text: qsTr(modelData)
							}
						}
					}
					
					RowLayout {
						Repeater {
							model: prefRoles
							Text {
								text: qsTr(modelData.platform + ": " + modelData.prefRole)
							}
						}
					}
					
					Text {
						visible: limitation ? true : false
						text: qsTr(limitation)
					}
					
					Text {
						visible: url.toString() ? true : false
						text: qsTr(url.toString())
					}
					
					Text {
						visible: notes ? true : false
						text: qsTr(notes)
					}
				}
			}
		}
	}

	delegate: softListDelegate
	ScrollBar.vertical: ScrollBar {}
}
