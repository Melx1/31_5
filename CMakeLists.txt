cmake_minimum_required(VERSION 3.21)
project(31_5)

set(CMAKE_CXX_STANDARD 14)

add_executable(31_5_1 31.5.1.cpp)
add_executable(31_5_2 31.5.2.cpp IGraph.h ListGraph.cpp ListGraph.h MatrixGraph.cpp MatrixGraph.h)