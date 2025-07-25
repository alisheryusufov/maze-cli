# Maze CLI

A simple C++ command‑line tool to generate and optionally solve perfect mazes.

## Features
- **Generate** random perfect maze (depth‑first search backtracker).
- **Solve** maze via breadth‑first search, highlighting the path.
- **ASCII‑art** output.

## Requirements
- C++17 compiler (g++, clang++, MSVC)
- CMake ≥ 3.10

## Building

```bash
mkdir build
cd build
cmake ..
make
