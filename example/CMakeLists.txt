cmake_minimum_required(VERSION 3.20)
project(r82labs_learn_with_physics_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  r82labs_learn_with_physics
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

FetchContent_MakeAvailable(r82labs_learn_with_physics)

add_executable(example_consumer main.cpp)

target_link_libraries(example_consumer PRIVATE r82labs_learn_with_physics)
