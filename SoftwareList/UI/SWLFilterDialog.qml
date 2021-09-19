// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15

import SWList 1.0

Dialog {
	width: parent.width * 0.95
	contentHeight: mainContent.contentHeight < parent.height * 0.5 ? mainContent.contentHeight : parent.height * 0.5
	anchors.centerIn: parent
	
	contentItem: ListView {
		id: mainContent
		anchors {
			leftMargin: 2
			rightMargin: 2
		}
		reuseItems: true
		clip: true
		spacing: 5
		
		model: ModelProvider.filterOptionsModel
		
		Component {
			id: filterSectionDelegate
			Rectangle {
				width: ListView.view.width
				height: childrenRect.height + 4
				color: "#DDDDDD"
				
				required property string section
				
				Label {
					text: qsTr(section)
					font.underline: true
				}
			}
		}
		
		Component {
			id: filterDelegate
			Flow {
				width: ListView.view.width
				height: childrenRect.height
				
				required property var filterOptions
				
				Repeater {
					model: filterOptions
					CheckBox {
						text: qsTr(modelData.filter)
						onCheckedChanged: modelData.isSelected = checked
						
						Component.onCompleted: checked = modelData.isSelected
					}
				}
			}
		}
		
		section {
			property: "filterType"
			criteria: ViewSection.FullString
			delegate: filterSectionDelegate
		}
		
		delegate: filterDelegate
		ScrollBar.vertical: ScrollBar {}
	}
	
	standardButtons: Dialog.Apply | Dialog.Cancel
}
