cmake_minimum_required(VERSION 3.16)

project(services LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(services
    src/CollectionService.cpp
    src/collections.cpp
    src/points.cpp
    src/search.cpp
    src/system_startup.cpp
    src/upsert_points.cpp
)

target_link_libraries(services PUBLIC collection)

target_include_directories(services PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Tests
option(BUILD_TESTS "Build Services module tests" OFF)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB SERVICES_TEST_FILES tests/*.cpp)

    add_executable(unit_tests ${SERVICES_TEST_FILES})

    target_link_libraries(unit_tests PRIVATE
        services
        GTest::gtest
        GTest::gtest_main
    )

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
