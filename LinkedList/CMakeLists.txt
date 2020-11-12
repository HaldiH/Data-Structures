cmake_minimum_required(VERSION 3.15)
project(TP2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TP2 main.c LinkedList.c)