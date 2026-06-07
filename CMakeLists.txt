cmake_minimum_required(VERSION 3.20)
project(r82labs_learn_with_physics VERSION 0.1.0 LANGUAGES CXX)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    option(BUILD_TESTING "Build unit tests" ON)
else()
    option(BUILD_TESTING "Build unit tests" OFF)
endif()

add_library(r82labs_learn_with_physics SHARED src/library.cpp)

target_include_directories(r82labs_learn_with_physics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

if(BUILD_TESTING)
    include(CTest)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(r82labs_learn_with_physics_tests
        tests/test_library.cpp
    )

    target_link_libraries(r82labs_learn_with_physics_tests
        PRIVATE
            r82labs_learn_with_physics
            gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(r82labs_learn_with_physics_tests)
endif()

include(CMakePackageConfigHelpers)

install(TARGETS r82labs_learn_with_physics
    EXPORT r82labs_learn_with_physicsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

install(EXPORT r82labs_learn_with_physicsTargets
    FILE r82labs_learn_with_physicsTargets.cmake
    NAMESPACE r82labs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r82labs_learn_with_physics
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/PackageConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/r82labs_learn_with_physicsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r82labs_learn_with_physics
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/r82labs_learn_with_physicsConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/r82labs_learn_with_physicsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/r82labs_learn_with_physicsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r82labs_learn_with_physics
)
