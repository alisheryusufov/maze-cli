#include "Maze.hpp"
#include <iostream>
#include <cstdlib>

void printUsage(const char* prog) {
    std::cout
      << "Usage:\n"
      << "  " << prog << " <width> <height> [--solve]\n"
      << "    width, height : integers > 1\n"
      << "    --solve       : also display solution path\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printUsage(argv[0]);
        return 1;
    }

    int width  = std::atoi(argv[1]);
    int height = std::atoi(argv[2]);
    bool solve = (argc==4 && std::string(argv[3])=="--solve");

    if (width < 2 || height < 2) {
        std::cerr << "Error: width and height must be > 1\n";
        return 1;
    }

    Maze maze(width, height);
    maze.generate();

    auto path = solve ? maze.solve() : std::vector<std::pair<int,int>>{};
    if (solve && path.empty()) {
        std::cerr << "No solution found.\n";
    }

    maze.print(path);
    return 0;
}
