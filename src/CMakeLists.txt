#CMakeLists for mapbuilder program

cmake_minimum_required (VERSION 2.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

#add_subdirectory(graphics)
add_subdirectory(yspng)
add_subdirectory(mapbuilder)
