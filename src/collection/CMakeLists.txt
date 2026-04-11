cmake_minimum_required(VERSION 3.16)

project(services LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(collection STATIC
    src/manage_collections.cpp
    src/points.cpp
    src/CollectionManager.cpp
    src/access_collection.cpp
)

target_link_libraries(collection PUBLIC storage)

target_include_directories(collection PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Tests
option(BUILD_TESTS "Build Collection module tests" OFF)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    file(GLOB COLLECTION_TEST_FILES tests/*.cpp)

    add_executable(collection_tests ${COLLECTION_TEST_FILES})

    target_link_libraries(collection_tests PRIVATE
        collection
        GTest::gtest
        GTest::gtest_main
    )

    add_test(NAME unit_tests COMMAND unit_tests)
endif()