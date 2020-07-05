@echo off


REM  Grab submodules
REM ---------------------------------------------------
git submodule update --init --recursive


REM  Delete existing buildfiles
REM ---------------------------------------------------
rmdir /q /s build


REM  Call meson
REM ---------------------------------------------------
meson setup build %meson_vars%


REM  Build hatchet
REM ---------------------------------------------------
cd build
ninja
cd ..