cmake_minimum_required(VERSION 3.16)
project(zoro_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(YAML-CPP REQUIRED)

# Engine library

set(ENGINE_SOURCES
    src/config.cpp
    src/storage/storage.cpp
    src/storage/collection.cpp
    core/version.cpp
)

set(ENGINE_HEADERS
    include/config.hpp
    include/storage/storage.hpp
    include/storage/collection.hpp
    core/version.hpp
)

add_library(engine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

target_link_libraries(engine PRIVATE yaml-cpp)

# CLI executable

add_executable(engine_cli
    main.cpp
    ${ENGINE_SOURCES}
)

target_include_directories(engine_cli PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

target_link_libraries(engine_cli PRIVATE yaml-cpp engine)

# Copy config.yaml to build/bin/
configure_file(${CMAKE_SOURCE_DIR}/config.yaml
               ${CMAKE_BINARY_DIR}/bin/config.yaml COPYONLY)

               include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

target_link_libraries(engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(engine_cli PRIVATE nlohmann_json::nlohmann_json)
