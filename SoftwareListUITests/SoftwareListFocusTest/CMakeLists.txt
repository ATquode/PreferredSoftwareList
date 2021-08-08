# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
	SWListFocusVisibilityTest
	../../SoftwareList/qml.qrc ../UITestServer.h main.cpp
)

add_test(NAME SoftwareListFocusVisibility COMMAND SWListFocusVisibilityTest)
target_compile_definitions(
	SWListFocusVisibilityTest
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(
	SWListFocusVisibilityTest PRIVATE Qt5::Core Qt5::Quick gtest Spix
)
