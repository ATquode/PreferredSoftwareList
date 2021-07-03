# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.14)

project(PreferredSoftwareList)

add_subdirectory(SoftwareList)

set(CMAKE_FORMAT_EXCLUDE SoftwareList/extra_helper/*|FormatterTarget/*)
add_subdirectory(FormatterTarget)
