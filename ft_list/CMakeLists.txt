cmake_minimum_required(VERSION 3.19)
project(ft_list_test)

set(CMAKE_CXX_STANDARD 98)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
add_compile_options(-Wall -Wextra -Werror)
include_directories(ft_list/)
target_precompile_headers(ft_list_test PRIVATE stdafx.h)
add_executable(ft_list_test ft_list.cpp
                            ft_list_test.cpp)