# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# cmake-format: off
add_executable(
	SWListFocusVisibilityTest
	main.cpp
	../UITestServer.h
	../../SoftwareList/qml.qrc
)
# cmake-format: on
add_test(NAME SoftwareListFocusVisibility COMMAND SWListFocusVisibilityTest)
target_compile_definitions(
	SWListFocusVisibilityTest
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
# cmake-format: off
target_link_libraries(
	SWListFocusVisibilityTest
	PRIVATE
		Qt5::Core
		Qt5::Quick
		GTest::GTest
		Spix::Spix
)
# cmake-format: on
