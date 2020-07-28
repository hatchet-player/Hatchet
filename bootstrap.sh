#! /usr/bin/env bash

# Grab submodules
#---------------------------------------------------
git submodule update --init --recursive


# Delete existing buildfiles
#---------------------------------------------------
rm -rf build


# Call meson
#---------------------------------------------------
meson setup build -Dprefix="/usr"


# Build hatchet
#---------------------------------------------------
cd build
ninja
