#include <Solver.h>
#include <Direction.h>
#include <Position.h>
#include <Grid.h>

#include <vector>
#include <string>

#include <iostream>

int main() {

    std::vector<std::string> tiles;

    tiles.push_back("grass");
    tiles.push_back("grass-sky");
    tiles.push_back("sky");
    tiles.push_back("bird");   

    Solver solver = Solver(tiles);

    solver.addAdjacencyConstraints(0, Direction::UP, {0, 1});
    solver.addAdjacencyConstraints(0, Direction::DOWN, {0});
    solver.addAdjacencyConstraints(0, Direction::LEFT, {0});
    solver.addAdjacencyConstraints(0, Direction::RIGHT, {0});

    solver.addAdjacencyConstraints(1, Direction::UP, {2});
    solver.addAdjacencyConstraints(1, Direction::DOWN, {0});
    solver.addAdjacencyConstraints(1, Direction::LEFT, {1});
    solver.addAdjacencyConstraints(1, Direction::RIGHT, {1});

    solver.addAdjacencyConstraints(2, Direction::UP, {2,3});
    solver.addAdjacencyConstraints(2, Direction::DOWN, {1,2,3});
    solver.addAdjacencyConstraints(2, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraints(2, Direction::RIGHT, {2,3});

    solver.addAdjacencyConstraints(3, Direction::UP, {2,3});
    solver.addAdjacencyConstraints(3, Direction::DOWN, {2,3});
    solver.addAdjacencyConstraints(3, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraints(3, Direction::RIGHT, {2,3});

    auto grid = solver.solve(5);

    // for (int i = 0; i < 4; i++) {
    //   for (int j = 0; j < 4; j++) {
    //     std::cout << "Position: (" << i << ", " << j << ")\nKey: " << grid.getKey({i, j});
    //   }
    // }

    return 0;
}