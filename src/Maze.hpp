
#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <utility>

class Maze {
public:
    Maze(int width, int height);

    // carve out the maze
    void generate();
    // find shortest path from (0,0) to (w-1,h-1)
    std::vector<std::pair<int,int>> solve();
    // print ASCII; pass the solve() path to draw it
    void print(const std::vector<std::pair<int,int>>& path = {}) const;

private:
    int w, h;
    struct Cell {
        bool walls[4];  // N, E, S, W
        bool visited;
    };
    std::vector<Cell> cells;

    int index(int x, int y) const { return y*w + x; }
    bool isValid(int x, int y) const { return x >= 0 && x < w && y >= 0 && y < h; }
};

#endif // MAZE_HPP
