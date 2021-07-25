# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
	Qt5
	COMPONENTS Core Quick
	REQUIRED
)
find_package(GTest REQUIRED)
find_package(Spix REQUIRED)

add_executable(CategoryListUITest main.cpp ../../SoftwareList/qml.qrc)
add_test(NAME CategoryListUIControl COMMAND CategoryListUITest)
target_compile_definitions(
	CategoryListUITest
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
# cmake-format: off
target_link_libraries(
	CategoryListUITest
	PRIVATE
		Qt5::Core
		Qt5::Quick
		GTest::GTest
		Spix::Spix
)
# cmake-format: on
