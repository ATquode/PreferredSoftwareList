# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.14)

project(PreferredSoftwareList)

option(PSWLIST_BUILD_TESTS "Build Unit and UI Tests on supported platforms" ON)

if(NOT DEFINED ENV{CPM_SOURCE_CACHE})
	set(ENV{CPM_SOURCE_CACHE} ${CMAKE_CURRENT_LIST_DIR}/build-CPMSrcCache)
endif()
include(cmake/CPM.cmake)

add_subdirectory(SoftwareList)
if(NOT ANDROID
	AND NOT IOS
	AND PSWLIST_BUILD_TESTS
)
	add_subdirectory(SoftwareListTests)
	add_subdirectory(SoftwareListUITests)
endif()

set(CMAKE_FORMAT_EXCLUDE
	SoftwareList/extra_helper/*|FormatterTarget/*|cmake/CPM.cmake
)
add_subdirectory(FormatterTarget)
