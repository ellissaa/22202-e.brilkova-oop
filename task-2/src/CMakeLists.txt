cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        GameOfLife.exe
        main.cpp
        ArgParser.cpp
        CommandParser.cpp
        Reader.cpp
        Universe.cpp
        Writer.cpp
)