cmake_minimum_required(VERSION 3.16)

project(zoro_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# CLI wrapper
file(GLOB CLI_SOURCES
    cli/cli.cpp
    cli/src/*.cpp 
)

add_library(zoro_api STATIC
    ${CLI_SOURCES}
)


target_include_directories(zoro_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cli
    ${CMAKE_CURRENT_SOURCE_DIR}/cli/include
)

target_link_libraries(zoro_api
    services
)

# C API 
add_library(zoro SHARED
    rest/c_api/zoro_c_api.cpp
)

target_include_directories(zoro PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(zoro
    services
    collection
    storage
    wal
)