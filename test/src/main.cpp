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


    int seed;
    std::cin >> seed;
    Solver solver = Solver(tiles, seed);

    solver.addAdjacencyConstraint(0, Direction::UP, {0, 1});
    solver.addAdjacencyConstraint(0, Direction::DOWN, {0});
    solver.addAdjacencyConstraint(0, Direction::LEFT, {0});
    solver.addAdjacencyConstraint(0, Direction::RIGHT, {0});

    solver.addAdjacencyConstraint(1, Direction::UP, {2});
    solver.addAdjacencyConstraint(1, Direction::DOWN, {0});
    solver.addAdjacencyConstraint(1, Direction::LEFT, {1});
    solver.addAdjacencyConstraint(1, Direction::RIGHT, {1});

    solver.addAdjacencyConstraint(2, Direction::UP, {2,3});
    solver.addAdjacencyConstraint(2, Direction::DOWN, {1,2,3});
    solver.addAdjacencyConstraint(2, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraint(2, Direction::RIGHT, {2,3});

    solver.addAdjacencyConstraint(3, Direction::UP, {2,3});
    solver.addAdjacencyConstraint(3, Direction::DOWN, {2,3});
    solver.addAdjacencyConstraint(3, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraint(3, Direction::RIGHT, {2,3});

    // solver.setInitialConstraint({3,3}, {0});

    solver.registerOnCollapse([&tiles](const Solver::TileKey& k, Position p){
        auto [i, j] = p;
        std::cout << "Collapse! at Position: (" << i << ", " << j << "), tile: " << tiles[k] << std::endl;
    });

    auto grid = solver.solve(5);

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        std::cout << "Position: (" << i << ", " << j << "), tile: " << tiles[grid.getKey({i, j})] << std::endl;
      }
    }

    return 0;
}