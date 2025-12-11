cmake_minimum_required(VERSION 3.16)

project(cli LANGUAGES CXX)

file(GLOB CLI_SOURCES *.cpp)
file(GLOB CLI_HEADERS *.h)

add_library(cli STATIC
    ${CLI_SOURCES}
    ${CLI_HEADERS}
)

target_include_directories(cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
