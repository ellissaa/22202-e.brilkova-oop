cmake_minimum_required(VERSION 3.16)
project(lab0b)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp ReadFile.cpp WriteFile.cpp
        Parser.cpp WordMap.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        LabTests
        tests/ReadFileTest.cpp
        tests/WriteFileTest.cpp
        tests/ParserTest.cpp
        tests/WordMapTest.cpp
        ReadFile.cpp
        WriteFile.cpp
        Parser.cpp
        WordMap.cpp
)

target_link_libraries(
        LabTests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(LabTests)