cmake_minimum_required(VERSION 3.15)
project(Containers)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(forward_list forward_list.c)
add_library(stack stack.c)
add_library(queue queue.c)
add_library(map map.c)
add_executable(test main.c forward_list.c stack.c queue.c map.c)
