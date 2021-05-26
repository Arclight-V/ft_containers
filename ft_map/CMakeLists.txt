cmake_minimum_required(VERSION 3.19)
project(ft_map_test)

set(CMAKE_CXX_STANDARD 98)
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
add_compile_options(-Wall -Wextra -Werror)
include_directories(~/)
include_directories(./test)
include_directories(../common_templates)
add_executable(ft_map_test ./test/ft_map_test.cpp)
target_precompile_headers(ft_map_test PRIVATE
        ../common_templates/stdafx.h)