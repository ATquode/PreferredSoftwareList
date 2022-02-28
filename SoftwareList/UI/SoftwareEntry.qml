// SPDX-FileCopyrightText: 2022 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.qmlmodels 1.0

ApplicationWindow {
	ScrollView {
		anchors.fill: parent
		property real cWidth: tableView.childrenRect.width + 7*2
		property real cHeight: clout.childrenRect.height - noteScroll.height + 80 + 7*2
		contentWidth: cWidth > parent.width - 20 ? cWidth : parent.width - 20
		contentHeight: cHeight > parent.height - 5 ? cHeight : parent.height - 5
		clip: true

		Item {
			anchors.fill: parent
			anchors.margins: 7

			ColumnLayout {
				id: clout
				anchors.fill: parent
				RowLayout {
					Label {
						text: qsTr("Name:")
					}
					TextField {
						Layout.fillWidth: true
					}
				}

				TableView {
					id: tableView
					Layout.fillWidth: true
//					Layout.minimumHeight: 20
					Layout.preferredHeight: 16 + ((tbm.rowCount - 1) * 32.5) + ((tbm.rowCount - 1) * 5) + 10
					rowHeightProvider: function (row) {
						if (row === 0) {
							return 16
						}
						return 32.5;
					}

					Layout.leftMargin: 10
					Layout.rightMargin: 10
					Layout.topMargin: 10
					columnSpacing: 5
					rowSpacing: 5
//					columnWidthProvider: function (column) { return 300; }

					model: TableModel {
						id: tbm
						TableModelColumn { display: "Category" }
						TableModelColumn { display: "Platform" }
						TableModelColumn { display: "Role" }
						TableModelColumn { display: "Button" }
						rows: [
							{
								Category: "Category",
								Platform: "Platform",
								Role: "Preferred Role",
								Button: ""
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							},
							{
								Category: 0,
								Platform: 1,
								Role: 2
							}
						]
					}

					delegate: DelegateChooser {
						DelegateChoice {
							row: 0
							delegate: Label {
								text: display
								horizontalAlignment: Qt.AlignHCenter
							}
						}

						DelegateChoice {
							column: 0
							delegate: ComboBox {
								currentIndex: display
								model: ["a", "a11", "a21"]
							}
						}

						DelegateChoice {
							column: 1
							delegate: ComboBox {
								currentIndex: display
								model: ["b", "b1", "b2"]
							}
						}

						DelegateChoice {
							column: 2
							delegate: ComboBox {
								currentIndex: display
								model: ["c", "c1", "c2"]
							}
						}

						DelegateChoice {
							column: 3
							delegate: Button {
								text: qsTr("Remove")
							}
						}
					}
				}

				Button {
					text: qsTr("Add")
					Layout.bottomMargin: 10
				}

				RowLayout {
					Label {
						text: qsTr("Limitation:")
					}
					TextField {
						Layout.fillWidth: true
					}
				}

				RowLayout {
					Label {
						text: qsTr("URL:")
					}
					TextField {
						Layout.fillWidth: true
					}
				}

				RowLayout {
					Label {
						text: qsTr("Notes:")
					}
					ScrollView {
						id: noteScroll
						Layout.fillWidth: true
						Layout.fillHeight: true
						Layout.minimumHeight: 80
						TextArea {}
					}
				}

				RowLayout {
					Layout.alignment: Qt.AlignRight
					Button {
						text: qsTr("OK")
					}
					Button {
						text: qsTr("Cancel")
						onClicked: close()
					}
				}
			}
		}
	}

	Component.onCompleted: {
		width = tableView.childrenRect.width + 7*2 + 10; // 10 - Fix for windows, macos
		height = clout.childrenRect.height + 7*2;
	}
}
