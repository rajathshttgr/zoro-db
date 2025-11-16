# Tests

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(engine_tests
    test_version.cpp
)

target_link_libraries(engine_tests
    PRIVATE
    gtest_main
    engine
)

include(GoogleTest)
gtest_discover_tests(engine_tests)
