cmake_minimum_required(VERSION 3.24)

add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Wundef -Wunreachable-code -Wstrict-aliasing -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wcast-qual -Wcast-align)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Additional flags for GCC
    add_compile_options(-Wuseless-cast)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Additional flags for Clang
    add_compile_options(-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-unused-macros -Wno-padded)
endif ()

add_executable(MyStack main.cpp base_array.cpp base_array.hpp my_stack.cpp my_stack.hpp)

