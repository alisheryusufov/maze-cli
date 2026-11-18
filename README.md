# Maze CLI

A C++ command-line tool to generate perfect mazes and optionally display their solution paths.

## Features

- **Generation:** randomized depth-first search backtracker.
- **Solving:** breadth-first search.
- **Display:** ASCII output in the terminal.

## Requirements

- C++17 compiler, such as GCC, Clang or MSVC
- CMake 3.10 or newer

## Build

From the repository root:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Usage

```text
maze-cli <width> <height> [--solve]
```

Both dimensions must be integers greater than 1. Add `--solve` to display the solution path.

For a single-configuration build on Linux or macOS, run from the build directory:

```bash
./maze-cli 20 10
./maze-cli 20 10 --solve
```

For a Visual Studio Release build on Windows, run from the build directory:

```powershell
.\Release\maze-cli.exe 20 10 --solve
```

The executable location depends on the CMake generator and build configuration.

## Project structure

- [`src/main.cpp`](src/main.cpp): command-line arguments and program entry point
- [`src/Maze.hpp`](src/Maze.hpp): maze interface
- [`src/Maze.cpp`](src/Maze.cpp): maze generation, solving and rendering
- [`CMakeLists.txt`](CMakeLists.txt): build configuration

## License

See [LICENSE](LICENSE).
