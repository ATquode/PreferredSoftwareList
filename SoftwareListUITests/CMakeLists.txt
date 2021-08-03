# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

project(SoftwareListUITests)

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

include_directories(.)

add_subdirectory(CategoryListTest)
add_subdirectory(SoftwareListFocusTest)
