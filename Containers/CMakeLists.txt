cmake_minimum_required(VERSION 3.15)
project(Containers)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_library(forward_list forward_list.c)
add_executable(test main.c forward_list.c)
add_library(stack stack.c)
add_library(queue queue.c)
