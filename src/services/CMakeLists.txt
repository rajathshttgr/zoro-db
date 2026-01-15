cmake_minimum_required(VERSION 3.16)

project(services LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SERVICES_HEADERS include/*.h)
file(GLOB SERVICES_SOURCES src/*.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(services
    src/CollectionService.cpp
    src/CollectionService_collections.cpp
    src/CollectionService_points.cpp
    src/CollectionService_search.cpp
    include/CollectionService.h
)

target_link_libraries(services PUBLIC collection)

target_include_directories(services PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tests
option(SERVICES_BUILD_TESTS "Build Services module tests" OFF)

if(SERVICES_BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB SERVICES_TEST_FILES tests/*.cpp)

    add_executable(services_tests ${SERVICES_TEST_FILES})

    target_link_libraries(services_tests PRIVATE
        services
        GTest::gtest
        GTest::gtest_main
    )

    add_test(NAME services_tests COMMAND services_tests)
endif()
