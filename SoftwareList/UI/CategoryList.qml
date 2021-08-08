// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
	reuseItems: true
	spacing: 10

	focus: true
	keyNavigationWraps: true

	property bool isMobile: false
	property int selectedIndex: 0
	property color defaultColor: "#EEEEEE"
	property color selectedColor: "#00DD55"
	property color hoverColor: Qt.lighter(selectedColor, 1.75)

	signal itemSelected(int index)

	Component {
		id: catDelegate
		Rectangle {
			id: catItemRect
			objectName: "listItem_" + index
			width: ListView.view.width
			height: 30
			color: isSelected ? selectedColor : isHovered ? hoverColor : defaultColor
			border {
				width: 2
				color: isHovered ? hoverColor : isSelected ? selectedColor : defaultColor
			}
			clip: true

			required property int index
			required property string display

			property bool isSelected: selectedIndex === catItemRect.index
			property bool isHovered: catItemHoverHandler.hovered || catItemRect.activeFocus //consider currentItem as hovered too, for keyboard navigation

			RowLayout {
				anchors.fill: parent

				Label {
					text: qsTr(display)
					Layout.fillWidth: true
					leftPadding: 10
				}

				Label {
					text: "\u25B6"
					rightPadding: 10
					visible: isMobile
				}
			}

			TapHandler {
				onTapped: itemSelected(index)
			}

			Keys.onPressed: {
				switch(event.key) {
				case Qt.Key_Space:
				case Qt.Key_Return:
					itemSelected(index);
					event.accepted = true;
				}
			}

			HoverHandler {
				id: catItemHoverHandler
			}
		}
	}

	delegate: catDelegate
	ScrollBar.vertical: ScrollBar {}
}
