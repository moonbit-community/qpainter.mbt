cmake_minimum_required(VERSION 3.10.0)
project(qpainter_mbt VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=undefined")
file(TO_CMAKE_PATH $ENV{QT6_INCLUDE} QT6_INCLUDE)
file(TO_CMAKE_PATH $ENV{MOON_HOME} MOON_HOME)

set(moonbit_runtime_source ${MOON_HOME}/lib/runtime.c)

add_library(runtime_mbt STATIC ${moonbit_runtime_source})
add_library(${PROJECT_NAME} STATIC stub.cxx)

link_directories($ENV{MSYS2}/bin)
include_directories(${MOON_HOME}/include)
include_directories(${QT6_INCLUDE})
include_directories(${QT6_INCLUDE}/QtGui)
include_directories(${QT6_INCLUDE}/QtWidgets)