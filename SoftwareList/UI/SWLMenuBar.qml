// SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
//
// SPDX-License-Identifier: MIT

//import Qt.labs.platform 1.1
import QtQml.Models 2.15
import QtQuick.Controls 2.15

import SWList 1.0

MenuBar {
	signal menuToggled(int menuType, string menuValue, bool isChecked)
	
	Menu {
		id: filterMenu
		title: qsTr("\&Filter")
		
		Instantiator {
			model: ModelProvider.filterOptionsModel
			
			delegate: Menu {
				id: filterTypeMenu
				title: qsTr(filterType)
				
				Instantiator {
					model: filterOptions
					
					delegate: MenuItem {
						text: qsTr(modelData.filter)
						checkable: true
						onCheckedChanged: menuToggled(filterItemRole, text, checked)
					}
					
					onObjectAdded: filterTypeMenu.insertItem(index, object)
					onObjectRemoved: filterTypeMenu.removeItem(object)
				}
			}
			
			onObjectAdded: filterMenu.insertMenu(index, object)
			onObjectRemoved: filterMenu.removeMenu(object)
		}
	}
}
