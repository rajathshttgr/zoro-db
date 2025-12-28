cmake_minimum_required(VERSION 3.16)
project(wal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB WAL_HEADERS include/*.h)
file(GLOB WAL_SOURCES src/*.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(wal STATIC
    ${WAL_SOURCES}
    ${WAL_HEADERS}
)

target_include_directories(wal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tests
option(WAL_BUILD_TESTS "Build WAL component tests" OFF)

if(WAL_BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB WAL_TEST_FILES tests/*.cpp)

    add_executable(wal_tests ${WAL_TEST_FILES})

    target_link_libraries(wal_tests PRIVATE
        wal
        GTest::gtest
        GTest::gtest_main
    )

    add_test(NAME wal_tests COMMAND wal_tests)
endif()
