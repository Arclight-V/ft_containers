cmake_minimum_required(VERSION 3.19)
project(ft_queue)

set(CMAKE_CXX_STANDARD 98)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")
add_compile_options(-Wall -Wextra -Werror)
include_directories(~/)
include_directories(./test)
add_executable(queue_test ./test/queue_test.cpp)

