cmake_minimum_required(VERSION 3.13)
project(SuanfaXinjie)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/tree src/my_utils)

add_executable(SuanfaXinjie src/main.cpp src/tree/bst.h src/tree/bst_utils.h src/my_utils/stl_utils.h)
