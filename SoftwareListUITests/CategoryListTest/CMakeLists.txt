# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(
	CategoryListUITest
	${APP_SOURCES} ../../SoftwareList/qml.qrc ../UITestServer.h main.cpp
)

add_test(NAME CategoryListHoverFocus COMMAND CategoryListUITest)
target_compile_definitions(
	CategoryListUITest
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_include_directories(CategoryListUITest PRIVATE ../../SoftwareList)
target_link_libraries(
	CategoryListUITest PRIVATE Qt5::Core Qt5::Quick Qt5::Sql gtest Spix
)
