#include "Maze.hpp"
#include <random>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <map>

Maze::Maze(int width, int height)
 : w(width), h(height), cells(width*height)
{
    // initialize all walls closed, unvisited
    for (auto& c : cells) {
        c.visited = false;
        for (int i = 0; i < 4; ++i) c.walls[i] = true;
    }
}

void Maze::generate() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::stack<std::pair<int,int>> st;

    int visitedCount = 1;
    cells[index(0,0)].visited = true;
    st.push({0,0});

    while (!st.empty()) {
        auto [x,y] = st.top();
        std::vector<int> dirs = {0,1,2,3};
        std::shuffle(dirs.begin(), dirs.end(), gen);

        bool moved = false;
        for (int dir : dirs) {
            int nx = x, ny = y;
            switch (dir) {
                case 0: ny = y-1; break; // North
                case 1: nx = x+1; break; // East
                case 2: ny = y+1; break; // South
                case 3: nx = x-1; break; // West
            }
            if (isValid(nx,ny) && !cells[index(nx,ny)].visited) {
                // knock down walls
                cells[index(x,y)].walls[dir] = false;
                cells[index(nx,ny)].walls[(dir+2)%4] = false;
                cells[index(nx,ny)].visited = true;
                ++visitedCount;
                st.push({nx,ny});
                moved = true;
                break;
            }
        }
        if (!moved) st.pop();
    }

    // reset visited flags for solve()
    for (auto& c : cells) c.visited = false;
}

std::vector<std::pair<int,int>> Maze::solve() {
    std::queue<std::pair<int,int>> q;
    std::map<std::pair<int,int>,std::pair<int,int>> parent;

    int sx = 0, sy = 0;
    int tx = w-1, ty = h-1;

    q.push({sx,sy});
    cells[index(sx,sy)].visited = true;

    bool found = false;
    while (!q.empty() && !found) {
        auto [x,y] = q.front(); q.pop();
        if (x == tx && y == ty) { found = true; break; }

        for (int dir = 0; dir < 4; ++dir) {
            if (!cells[index(x,y)].walls[dir]) {
                int nx = x, ny = y;
                switch (dir) {
                    case 0: ny = y-1; break;
                    case 1: nx = x+1; break;
                    case 2: ny = y+1; break;
                    case 3: nx = x-1; break;
                }
                if (isValid(nx,ny) && !cells[index(nx,ny)].visited) {
                    cells[index(nx,ny)].visited = true;
                    parent[{nx,ny}] = {x,y};
                    q.push({nx,ny});
                }
            }
        }
    }

    std::vector<std::pair<int,int>> path;
    if (found) {
        auto cur = std::make_pair(tx,ty);
        while (!(cur.first==sx && cur.second==sy)) {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back({sx,sy});
        std::reverse(path.begin(), path.end());
    }
    return path;
}

void Maze::print(const std::vector<std::pair<int,int>>& path) const {
    // top border
    std::cout << "+";
    for (int i = 0; i < w; ++i) std::cout << "---+";
    std::cout << "\n";

    for (int y = 0; y < h; ++y) {
        // cells + vertical walls
        std::cout << "|";
        for (int x = 0; x < w; ++x) {
            bool onPath = false;
            for (auto& p : path)
                if (p.first==x && p.second==y) { onPath = true; break; }

            std::cout << (onPath ? " * " : "   ");
            std::cout << (cells[index(x,y)].walls[1] ? "|" : " ");
        }
        std::cout << "\n";

        // horizontal walls
        std::cout << "+";
        for (int x = 0; x < w; ++x) {
            std::cout << (cells[index(x,y)].walls[2] ? "---" : "   ");
            std::cout << "+";
        }
        std::cout << "\n";
    }
}
