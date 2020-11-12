cmake_minimum_required(VERSION 3.15)
project(TP3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(ex1 STATIC src/ex1.c src/forward_list.c)

add_executable(Exercise_1 src/main1.c)
target_link_libraries(Exercise_1 PUBLIC ex1)

add_executable(Exercise_2 src/main2.c src/ex2.c src/map.c)
target_link_libraries(Exercise_2 PUBLIC ex1)
