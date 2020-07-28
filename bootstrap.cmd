@echo off


REM  Delete existing buildfiles
REM ---------------------------------------------------
rmdir /q /s build


REM set path variables
REM ---------------------------------------------------
set prefix=C:\Hatchet
set path=%prefix%;%path%
set BOOST_ROOT=%prefix%\Boost
set PKG_CONFIG_PATH=%prefix%\lib\pkgconfig
set CMAKE_PREFIX_PATH=%prefix%;C:\Program Files;C:\Program Files (x86);


REM set path variables
REM ---------------------------------------------------
REM nested meson subprojects dont currently work
REM on MSCV. This promotes the nested subprojects.
meson wrap promote miniupnpc


REM  Call meson
REM ---------------------------------------------------
meson setup build ^
    %meson_vars% ^
    -Dcmake_prefix_path="%cmake_path%" ^
    -Dprefix="%prefix%"


REM  Build lucene
REM ---------------------------------------------------
cd build
%prefix%\bin\ninja
cd ..
