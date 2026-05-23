cmake_minimum_required(VERSION 4.2)
project(r82labs_learn_with_physics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(r82labs_learn_with_physics SHARED library.cpp)

target_include_directories(r82labs_learn_with_physics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(r82labs_learn_with_physics_tests
        tests/test_library.cpp
)

target_link_libraries(r82labs_learn_with_physics_tests
        PRIVATE
        r82labs_learn_with_physics
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(r82labs_learn_with_physics_tests)
