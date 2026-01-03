cmake_minimum_required(VERSION 3.16)

project(index LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(index STATIC
    vector_index.h
    index_factory.h
    faiss/faiss_index.h
    faiss/faiss_index.cpp
    faiss/faiss_id_map.h
    faiss/faiss_config.h
)

target_include_directories(index
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# FAISS (CPU only)
find_package(faiss REQUIRED)

target_link_libraries(index
    PRIVATE
        faiss
)

# Tests (TODO: Add tests later)
