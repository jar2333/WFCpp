#include "Test.h"

template <typename T>
void print(T a, std::string container) {
    std::cout << container << ": ";
    for (auto k : a) {
        std::cout << k << ", ";
    }
    std::cout << std::endl;
}

void SolverTester::testSolver() {
	std::vector<std::string> tiles;

    tiles.push_back("grass");
    tiles.push_back("grass-sky");
    tiles.push_back("sky");
    tiles.push_back("bird");   

    Solver solver = Solver(tiles, 3);

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
    solver.addAdjacencyConstraint(3, Direction::DOWN, {1,2,3});
    solver.addAdjacencyConstraint(3, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraint(3, Direction::RIGHT, {2,3});

    solver.setInitialConstraint({1,0}, {1});

    solver.registerOnCollapse([&tiles](const auto& k, Position p){
        auto [i, j] = p;
        std::cout << "Collapse! at Position: (" << i << ", " << j << "), tile: " << tiles[k] << std::endl;
    });

    solver.registerOnPropagate([](const auto& k, Position p){
        auto [i, j] = p;
        std::cout << "Propagate! at Position: (" << i << ", " << j << "), ";
        print(k, "tiles: ");
    });

    size_t gridSize = 4;

    std::cout << "Solving grid:\n";
    SolverGrid grid;
    solver.solve(gridSize, grid);

    std::cout << "Printing solved grid:\n";
    for (size_t i = 0; i < gridSize; i++) {
      for (size_t j = 0; j < gridSize; j++) {
        std::cout << "Position: (" << i << ", " << j << "), tile: " << tiles[grid.getKey({i, j})] << std::endl;
      }
    }

}

void SolverTester::runAll() {
    testSolver();
}