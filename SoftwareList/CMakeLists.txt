# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.14)

project(
	SoftwareList
	VERSION 0.1
	LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ~~~
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.
#
# if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
# endif()
# ~~~

find_package(
	QT NAMES Qt6 Qt5
	COMPONENTS Core Quick
	REQUIRED
)
find_package(
	Qt${QT_VERSION_MAJOR}
	COMPONENTS Core Quick
	REQUIRED
)

set(PROJECT_SOURCES
	Application.cpp
	main.cpp
	Model/CategoryModel.cpp
	Model/ModelProvider.cpp
	qml.qrc
)

set(PROJECT_HEADERS Application.h Model/CategoryModel.h Model/ModelProvider.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(SoftwareList MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
	if(ANDROID)
		add_library(SoftwareList SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})
	else()
		add_executable(SoftwareList ${PROJECT_SOURCES} ${PROJECT_HEADERS})
	endif()
endif()

target_compile_definitions(
	SoftwareList
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(
	SoftwareList
	PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
)

set_target_properties(
	SoftwareList
	PROPERTIES
		MACOSX_BUNDLE_GUI_IDENTIFIER pswl.softlist
		MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
		MACOSX_BUNDLE_SHORT_VERSION_STRING
			${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_import_qml_plugins(SoftwareList)
	qt_finalize_executable(SoftwareList)
endif()

if(IOS)
	include(extra_helper/QtStaticCmake.cmake)

	qt_generate_plugin_import(SoftwareList VERBOSE)
	# ~~~
	# from https://github.com/OlivierLDff/QQuickStaticHelloWorld/blob/master/CMakeLists.txt
	# EXTRA_PLUGIN are the one required by plugin loaded by qt_generate_plugin_import
	# It's not automatic yet :( All this workflow might change in future version
	# of qt with better and better cmake support
	# ~~~
	qt_generate_qml_plugin_import(
		SoftwareList
		QML_SRC ${CMAKE_CURRENT_SOURCE_DIR}
		EXTRA_PLUGIN
			# QtQuickVirtualKeyboardPlugin QtQuickVirtualKeyboardSettingsPlugin
			# QtQuickVirtualKeyboardStylesPlugin
			QmlFolderListModelPlugin QQuickLayoutsPlugin
		VERBOSE
	)

	include(extra_helper/AddQtIosApp.cmake)
	add_qt_ios_app(SoftwareList VERBOSE)
endif()
