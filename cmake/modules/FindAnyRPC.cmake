# SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>
#
# SPDX-License-Identifier: MIT

# C0103: naming convention. Doesn't apply in this case, since <package>_FOUND's
# <package> can have any case, and the case is preserved.
#
# cmake-lint: disable=C0103
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
