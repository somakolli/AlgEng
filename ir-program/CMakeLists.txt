cmake_minimum_required(VERSION 3.12)
project(ir_program)

set(CMAKE_CXX_STANDARD 17)

add_executable(ir_program main.cpp InvertedIndex.cpp InvertedIndex.h)