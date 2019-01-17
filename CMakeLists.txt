cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_STANDARD 11) # tODO move up to a general cmake config for all sub projects ?

project(CDT_2D)
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
