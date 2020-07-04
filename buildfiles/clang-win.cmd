@echo off

set prefix=C:\Program Files(x86)
set BOOST_ROOT=C:\local\Boost
set cmake_path=%prefix%;C:\Program Files;C:\Program Files (x86);

REM add attica to CMake Prefix
REM ---------------------------------------------------
set cmake_path=%cmake_path%;C:\Program Files\Attica;C:\Program Files (x86)\Attica

REM add sparsehash to CMake Prefix
REM ---------------------------------------------------
set cmake_path=%cmake_path%;C:\Program Files\sparsehash;C:\Program Files (x86)\sparsehash

set CMAKE_PREFIX_PATH="%cmake_path%"

REM Set meson variables
REM ---------------------------------------------------
set meson_vars=^
    --native-file ".\buildfiles\native\win-x86_64-clang.ini" ^
	-Ddefault_library=static ^
    -Dcmake_prefix_path="%cmake_path%" ^
    -Dprefix="%prefix%"


REM Call bootstrap
REM ---------------------------------------------------
.\bootstrap.cmd