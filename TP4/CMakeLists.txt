cmake_minimum_required(VERSION 3.15)
project(TP4 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(TP4 src/main.c src/forward_list.c src/queue.c src/stack.c)