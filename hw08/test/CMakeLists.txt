cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

add_executable(gtest_run my_stack_test.cpp ../src/base_array.hpp ../src/base_array.cpp ../src/my_stack.hpp ../src/my_stack.cpp)

target_link_libraries(
        gtest_run PRIVATE
        GTest::gtest
        GTest::gtest_main
)

enable_testing()

add_test(
        NAME test
        COMMAND gtest_run
)