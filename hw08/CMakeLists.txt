cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE "/Users/nx006/Documents/vscode/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "vcpkg toolchain file")

project(MyStack
        VERSION 1.0.0
        DESCRIPTION "MyStack"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
