cmake_minimum_required(VERSION 3.15)
project(TP3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Exercise_1 Exercise_1.c ../Containers/forward_list.c)

target_include_directories(Exercise_1 PUBLIC ../Containers/include)