# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

set(AnyRPC_FOUND TRUE)

# hacks
install(
	TARGETS anyrpc
	EXPORT SpixTargets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
add_library(AnyRPC::anyrpc ALIAS anyrpc)
