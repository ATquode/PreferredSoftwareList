// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ToolBar {
	property string pageTitle: "ToolBar"
	
	property alias backBtnVisible: backBtn.visible
	
	signal backBtnClicked
	signal filterBtnClicked
	
	ToolButton {
		id: backBtn
		text: "\u25C0"
		visible: false
		
		onClicked: backBtnClicked()
	}
	
	Label {
		anchors.centerIn: parent
		text: pageTitle
	}
	
	RowLayout {
		anchors.right: parent.right
		ToolButton {
			text: qsTr("Filter")
			onClicked: filterBtnClicked()
		}
	}
}
