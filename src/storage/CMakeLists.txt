cmake_minimum_required(VERSION 3.16)
project(storage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB STORAGE_HEADERS include/*.h)
file(GLOB STORAGE_SOURCES src/*.cpp)

add_library(storage STATIC
    ${STORAGE_SOURCES}
    ${STORAGE_HEADERS}
)

target_include_directories(storage PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tests
option(STORAGE_BUILD_TESTS "Build Storage component tests" OFF)

if(STORAGE_BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB STORAGE_TEST_FILES tests/*.cpp)

    add_executable(storage_tests ${STORAGE_TEST_FILES})

    target_link_libraries(storage_tests PRIVATE
        storage
        GTest::gtest
        GTest::gtest_main
    )

    add_test(NAME storage_tests COMMAND storage_tests)
endif()
