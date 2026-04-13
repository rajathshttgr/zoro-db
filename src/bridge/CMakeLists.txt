cmake_minimum_required(VERSION 3.16)

project(zoro_api LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# C API 
add_library(zoro SHARED
    src/zoro_c_api.cpp
    src/collections.cpp
    src/points.cpp
    src/search.cpp
)

target_link_libraries(zoro
    services
    collection
    index
    wal
    storage
    utils
)

target_include_directories(zoro PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)