#! /usr/bin/env bash

# Setup paths
#---------------------------------------------------
export prefix="/mnt/c/Program Files(x86)"
cmake_path="/mnt/c/Program Files:/mnt/c/Program Files (x86):${prefix}"


# Add attica to CMake Prefix
#---------------------------------------------------
cmake_path="${cmake_path}"


# Add sparsehash to CMake Prefix
#---------------------------------------------------
cmake_path="${cmake_path}"


# Set meson variables
#---------------------------------------------------
export CMAKE_PREFIX_PATH="${cmake_path}"


# Call Meson
#---------------------------------------------------
meson setup build \
    --cross-file "./buildfiles/cross/wsl-mingw-w64.x86_64-Windows.ini"
    -Ddefault_library="static"
    -Dprefix="${prefix}"
    -Dcmake_prefix_path="${cmake_path}"


# Build Tomahawk
#---------------------------------------------------
cd build
ninja
