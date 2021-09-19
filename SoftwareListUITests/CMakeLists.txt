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
	COMPONENTS Core Quick Sql
	REQUIRED
)

set(GTEST_OPTIONS "BUILD_GMOCK OFF")
if(MSVC)
	list(APPEND GTEST_OPTIONS "gtest_force_shared_crt ON")
endif()

CPMFindPackage(
	NAME GTest
	GITHUB_REPOSITORY google/googletest
	GIT_TAG 5b40153003d1a5ad7b8f40cffcd09434afda3428
	OPTIONS ${GTEST_OPTIONS}
)

CPMFindPackage(
	NAME AnyRPC
	GITHUB_REPOSITORY faaxm/anyrpc
	GIT_TAG 74b4fbb92b654a9483ef3ff64b708fda46bd7b2b
	OPTIONS
		"BUILD_EXAMPLES OFF"
		"BUILD_WITH_LOG4CPLUS OFF"
		"ANYRPC_LIB_BUILD_SHARED OFF"
)
# rest of the hacks are in cmake/modules/FindAnyRPC.cmake
target_include_directories(
	anyrpc PUBLIC $<BUILD_INTERFACE:${AnyRPC_SOURCE_DIR}/include>
)

CPMFindPackage(
	NAME Spix
	GITHUB_REPOSITORY faaxm/spix
	GIT_TAG 453e849145dee803f61c23b606448dc14177243a
	OPTIONS "SPIX_BUILD_EXAMPLES OFF"
)

include_directories(.)

set(APP_SOURCES
	../../SoftwareList/DB/DBManager.cpp
	../../SoftwareList/Model/CategoryListModel.cpp
	../../SoftwareList/Model/FilterOptionModel.cpp
	../../SoftwareList/Model/PlatformListModel.cpp
	../../SoftwareList/Model/ModelProvider.cpp
	../../SoftwareList/Model/SoftwareItem.cpp
	../../SoftwareList/Model/SoftwareItemModel.cpp
	../../SoftwareList/Model/SoftwareItemProxyModel.cpp
	../../SoftwareList/Model/SWItemRole.h
)

add_subdirectory(CategoryListTest)
add_subdirectory(SoftwareListFocusTest)
