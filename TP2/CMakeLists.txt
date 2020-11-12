cmake_minimum_required(VERSION 3.1)
project(TP2)

set(CMAKE_C_STANDARD 11)

include_directories(include)
add_executable(Exercise_1 Exercise_1.c forward_list.c stack.c)
add_executable(Exercise_2 Exercise_2.c forward_list.c queue.c)