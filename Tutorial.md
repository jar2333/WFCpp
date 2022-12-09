# WFCpp Tutorial

## Solver tutorial

This brief tutorial covers how to use the Solver module to invoke the WFC algorithm. We will use it to effectively tile a grid with strings, which will function as our set of tiles. We include the necessary headers:

```c++
#include <Solver.h>
#include <Grid.h>
#include <Direction.h>
#include <Position.h>

#include <iostream>
#include <vector>
#include <string>
```

Then, we specify a vector of strings as our tiles:
- Dirt tiles
- Grass tiles
- Sky tiles
- Bird tiles

```c++
std::vector<std::string> tiles;

tiles.push_back("dirt");
tiles.push_back("grass");
tiles.push_back("sky");
tiles.push_back("bird");   
```

We initialize a Solver with our vector of tiles, which automatically creates tile keys corresponding to the index in the vector.

```c++
Solver solver = Solver(tiles, 3);
```

Now, we can specify adjacency constraints for each tile:
- Dirt tiles can only be adjacent to other Dirt tiles, except above them, where they can also be adjacent to Grass tiles.
- Grass tiles can only only be adjacent to other Grass tiles on the sides. Below, they can only be adjacent to Dirt tiles. Above them, they can only be adjacent to Sky tiles.
- Sky tiles can only be adjacent to Bird and Sky tiles on all sides except below, where they can also be adjacent to Grass tiles.
- Bird tiles are functionally equivalent to Sky tiles.

```c++
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
```

We want to make it so that the final grid has a size of 4x4, and want the tile at coordinate (0, 2) to be Grass:

```c++
size_t N = 4;
solver.setInitialConstraint({0,2}, {1});
```

We register two callbacks, to print what occurs inside the Solver as it happens. Note, the type of the argument can be `auto`, but we explicitly name it to be precise. These callbacks can do anything you want! (printing to console, modifying some other structure, or even drawing to a window)

```c++
solver.registerOnCollapse([&tiles](const Solver::TileKey& k, Position p){
    auto [i, j] = p;
    std::cout << "Collapse! at Position: (" << i << ", " << j << "), tile: " << tiles[k] << std::endl;
});

solver.registerOnPropagate([](const std::vector<Solver::TileKey>& k, Position p){
    auto [i, j] = p;
    std::cout << "Propagate! at Position: (" << i << ", " << j << "), ";
    std::cout << "tiles: ";
    for (auto k : a) {
        std::cout << k << ", ";
    }
    std::cout << std::endl;
});

```

Now, we are ready to call the solver. We create a `SolverGrid` to store the results of the `solve` method.

```c++
std::cout << "Solving grid:\n";
SolverGrid grid;
solver.solve(N, grid);
```

We can now print the results of the algorithm, using the tile keys in the grid to print the actual tile! This grid can be passed to a `Synthesizer` to generate an output image, granted that the grid was given the necessary image information!

```c++
std::cout << "Printing solved grid:\n";
for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
    std::cout << "Position: (" << i << ", " << j << "), tile: " << tiles[grid.getKey({i, j})] << std::endl;
    }
}
```
