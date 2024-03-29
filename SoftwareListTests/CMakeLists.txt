# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

project(SoftwareListTests)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

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

set(TEST_SOURCES
	../SoftwareList/DB/DBManager.cpp
	../SoftwareList/Model/CategoryListModel.cpp
	../SoftwareList/Model/FilterOptionModel.cpp
	../SoftwareList/Model/SoftwareItem.cpp
	../SoftwareList/Model/SoftwareItemModel.cpp
	../SoftwareList/Model/SoftwareItemProxyModel.cpp
	../SoftwareList/Model/ContextualRole.h
	../SoftwareList/Model/PlatformListModel.h
	../SoftwareList/Model/PreferenceRoleListModel.h
	../SoftwareList/Model/ModelProvider.h
	../SoftwareList/Model/ContextualRoleTableModel.cpp
	Category/CategoryTests.cpp
	SoftwareItem/SoftwareModelTests.cpp
	SoftwareItem/SoftwareProxyModelTests.cpp
	SoftwareItem/ContextualRoleModelTests.cpp
	unittest_main.cpp
)

add_executable(SWListUnitTest ${TEST_SOURCES})

add_test(NAME SWListUnitTests COMMAND SWListUnitTest)
target_compile_definitions(
	SWListUnitTest
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_include_directories(SWListUnitTest PRIVATE ../SoftwareList)
target_link_libraries(
	SWListUnitTest PRIVATE Qt5::Core Qt5::Quick Qt5::Sql gtest
)
