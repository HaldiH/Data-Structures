cmake_minimum_required(VERSION 3.15)
project(TP3 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(ex1 SHARED src/ex1.c src/forward_list.c)

add_library(ex2 SHARED src/ex2.c src/map.c)

add_executable(Exercise_1 src/main1.c)
target_link_libraries(Exercise_1 PUBLIC ex1)

add_executable(Exercise_2 src/main2.c)
target_link_libraries(Exercise_2 PUBLIC ex1 ex2)
