cmake_minimum_required(VERSION 3.16)

project(utils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB UTILS_HEADERS *.h)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(utils
    struct.h
)

target_link_libraries(utils PUBLIC services)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
