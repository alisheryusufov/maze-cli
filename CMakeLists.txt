cmake_minimum_required(VERSION 3.10)
project(maze-cli VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(maze-cli
    src/main.cpp
    src/Maze.cpp
)
target_include_directories(maze-cli PRIVATE src)

