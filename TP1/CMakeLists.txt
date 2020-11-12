cmake_minimum_required(VERSION 3.1.0)
project(TP1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_executable(TP1 exercise_1.cpp exercise_2.cpp)
add_executable(TP1_C TP1.c Exercise1.c Exercise2.c)

target_link_libraries(TP1_C PUBLIC m)