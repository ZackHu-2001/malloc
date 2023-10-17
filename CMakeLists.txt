cmake_minimum_required(VERSION 3.22)
project(malloc)

set(CMAKE_CXX_STANDARD 17)

add_executable(malloc main.cpp
        LinkedList.cpp
        LinkedList.h)
