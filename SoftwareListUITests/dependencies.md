<!--
SPDX-FileCopyrightText: 2021 Rifat Hasan <atunutemp1@gmail.com>

SPDX-License-Identifier: CC0-1.0
-->

# googletest
https://github.com/google/googletest

    mkdir build && cd build && mkdir debugBuild && cd debugBuild
### Windows
    cmake -G"Visual Studio 16 2019" -DBUILD_GMOCK=OFF -Dgtest_force_shared_crt=ON "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..
### Linux, macOS
    cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_GMOCK=OFF "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..

and then

    cmake --build . --target install --config Debug

Replace debug with release for release builds.



# anyrpc
https://github.com/faaxm/anyrpc

    mkdir build && cd build && mkdir debugBuild && cd debugBuild
### Windows
    cmake -G"Visual Studio 16 2019" -DBUILD_EXAMPLES=OFF -DBUILD_WITH_LOG4CPLUS=OFF -DANYRPC_LIB_BUILD_SHARED=OFF "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..
### Linux, macOS
    cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_EXAMPLES=OFF -DBUILD_WITH_LOG4CPLUS=OFF -DANYRPC_LIB_BUILD_SHARED=OFF "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..

and then

    cmake --build . --target install --config Debug

Replace debug with release for release builds.



# spix
https://github.com/faaxm/spix

    mkdir build && cd build && mkdir debugBuild && cd debugBuild
### Windows
    cmake -DSPIX_BUILD_EXAMPLES=OFF "-DCMAKE_PREFIX_PATH=$Qt_Path;$AnyRPC_install_dir" "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..
### Linux, macOS
    cmake -DCMAKE_BUILD_TYPE=Debug -DSPIX_BUILD_EXAMPLES=OFF "-DCMAKE_PREFIX_PATH=$Qt_Path;$AnyRPC_install_dir" "-DCMAKE_INSTALL_PREFIX=../debugBin" ../..

and then

    cmake --build . --target install --config Debug

Replace debug with release for release builds.
