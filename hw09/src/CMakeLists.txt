cmake_minimum_required(VERSION 3.24)
project(shape)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(shape main.cpp shape.hpp)
