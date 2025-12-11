cmake_minimum_required(VERSION 3.16)
project(zoro-db LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(storage)
add_subdirectory(collection)
add_subdirectory(api/cli) 

add_executable(zoro-db
    main.cpp
)

target_link_libraries(zoro-db PRIVATE
    storage
    collection
    cli         
)
