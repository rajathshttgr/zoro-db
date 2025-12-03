cmake_minimum_required(VERSION 3.16)
project(zoro_engine LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Build shared library
add_library(zoro SHARED
src/collection.cpp
src/engine.cpp
src/storage.cpp
src/native_api.cpp
)


target_include_directories(zoro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Optional: link nlohmann_json if available (used for metadata)
find_package(nlohmann_json QUIET)
if (nlohmann_json_FOUND)
target_link_libraries(zoro PRIVATE nlohmann_json::nlohmann_json)
endif()


# Installation (optional)
install(TARGETS zoro LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)