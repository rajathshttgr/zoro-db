cmake_minimum_required(VERSION 3.16)

project(zoro_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Core API
add_library(zoro_core STATIC
    CollectionService.cpp
)

target_include_directories(zoro_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(zoro_core
    storage
    collection
)

# CLI wrapper
add_library(zoro_cli STATIC
    cli/cli.cpp
)

target_include_directories(zoro_cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(zoro_cli
    zoro_core
)


# C API 
add_library(zoro SHARED
    c_api/zoro_c_api.cpp
)

target_include_directories(zoro PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(zoro
    zoro_core
    storage
    collection
)