cmake_minimum_required(VERSION 3.16)

project(zoro_services LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SERVICES_HEADERS include/*.h)
file(GLOB SERVICES_SOURCES src/*.cpp)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(zoro_services STATIC
    ${SERVICES_SOURCES}
    ${SERVICES_HEADERS}
)

target_include_directories(zoro_services PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

