#include <Solver.h>

typedef Solver::TileKey TileKey;

/*
   INTERFACE
*/

void Solver::setSeed(int seed) {
    seed = seed;
    srand(seed);
}

int Solver::getSeed() {
    return seed;
}

//use move semantics?
Grid<TileKey> Solver::solve(int N) {
    Grid<TileKey> g = Grid<TileKey>(this->tiles, N);

    initializeGrid(N);

    while (!isCollapsed()) {
      iterate();
    }

    //can be moved down the call stack if required by algorithm logic, later
    if (isContradiction()) {
      throw std::runtime_error( "Encountered contradiction in solver." );
    }

    for (const auto& [p, tile] : this->grid) {
      TileKey k = tile[0];
      g.setKey(p, k);
    }

    return g;
  }

  void Solver::addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor) {
    adjacency_constraints[std::make_pair(t, d)].insert(neighbor);
  }

  void Solver::removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor) {
    adjacency_constraints[std::make_pair(t, d)].erase(neighbor);
  }

  void Solver::addAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors) {
    auto p = std::make_pair(t, d);
    for (auto n : neighbors) {
      adjacency_constraints[p].insert(n);
    }
  }

  void Solver::removeAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors) {
    auto p = std::make_pair(t, d);
    for (auto n : neighbors) {
      adjacency_constraints[p].erase(n);
    }
  }

  void Solver::setInitialConstraint(Position p, TileKey possibility) {
    initial_constraints[p].clear();
    initial_constraints[p].insert(possibility);
  }

  void Solver::setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities) {
    initial_constraints[p].clear(); 
    for (auto k : possibilities) {
      initial_constraints[p].insert(k);
    }
  }

  Solver::CollapseCallbackCookie Solver::registerOnCollapse(Solver::CollapseCallback callback) {
    return collapse_callbacks.insert(collapse_callbacks.begin(), callback);
  }

  void Solver::deregisterOnCollapse(Solver::CollapseCallbackCookie cookie) {
    collapse_callbacks.erase(cookie);
  }


  //API: calls registered function with possible tiles in collapsed grid slot
  Solver::PropagateCallbackCookie Solver::registerOnPropagate(Solver::PropagateCallback callback) {
    return propagate_callbacks.insert(propagate_callbacks.begin(), callback);
  }

  void Solver::deregisterOnCollapse(Solver::PropagateCallbackCookie cookie) {
    propagate_callbacks.erase(cookie);
  }

  void Solver::setCollapseBehaviour(std::optional<Solver::CollapseBehavior> b) {
    if (!b) {
      collapse_behavior = nullptr;
    }
    collapse_behavior = b.value();
  }

  /*
    ALGORITHM (optimize)
  */

  void Solver::initializeGrid(int N) {
    grid.clear();

    this->N = N;

    //populate grid
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        Position p{i, j};
        grid[p] = getPossibleTiles(p);
      }
    }

    //propagate initial constraints
    processInitialConstraints();
  }

  void Solver::processInitialConstraints() {
    for (const auto& [p, _] : this->initial_constraints) {
      propagate(p);
    }
  }

  void Solver::iterate() {
    Position p = getMinEntropyCoordinates();
    collapseAt(p);
    propagate(p);
  }

  //optimizations can be made using an instance variable
  bool Solver::isCollapsed() {
    for (const auto& [_, t] : this->grid) {
      if (t.size() > 1)
        return false;
    }
    return true;
  }

  //alternatively make this an exception?
  bool Solver::isContradiction() {
    for (const auto& [_, t] : this->grid) {
      if (t.size() == 0)
        return true;
    }
    return false;
  }

  Position Solver::getMinEntropyCoordinates() {
    Position min_entropy_position{0,0};
    size_t min_entropy = tiles.size();
    for (auto const [p, v] : grid) {
      if (v.size() < min_entropy && v.size() > 1) {
        min_entropy_position = p;
        min_entropy = v.size();
      }
    }
    return min_entropy_position;
  }

  void Solver::collapseAt(Position p) {
    std::vector<TileKey>& tiles = grid.at(p);
    
    auto it = [&](){
      if (collapse_behavior) {
        return collapse_behavior(tiles);
      }
      return collapseRandom(tiles);
    }();

    TileKey tile = *it;
    tiles.clear();
    tiles.push_back(tile);

    
    for (auto callback : collapse_callbacks) {
      callback(tile, p);
    }
  }

  void Solver::propagate(Position p) {
    std::stack<Position> stack;
    stack.push(p);

    while (!stack.empty()) {
      Position cur = stack.top();
      stack.pop();

      std::vector<Position> neighbors = getNeighbors(cur);

      for (Position n : neighbors) {
        if (propagateAt(cur, n)) {
          stack.push(n);
        }
      }
    }
  }

  //returns true if neighbor's possible tiles decrease
  bool Solver::propagateAt(Position current, Position neighbor) {
    std::vector<TileKey>& neighbor_tiles = grid[neighbor];
    size_t initial_amount = neighbor_tiles.size();

    std::vector<TileKey>& current_tiles = grid[current];

    Direction d = current.getDirection(neighbor);
    
    //for each tile in the current grid slot, check its set of allowed neighbors in the given direction
    //add that to an overall set of permitted tiles, which is then used to remove any which are not in this set
    std::unordered_set<TileKey> allowed;
    for (TileKey k : current_tiles) {
      
      auto adjacencies = getAdjacencies(k, d);
      //print(adjacencies, "Adjacencies");
      for (TileKey a : adjacencies) {
        allowed.insert(a);
      }
    }

    //remove non-allowed tiles
    auto it = std::remove_if(neighbor_tiles.begin(), neighbor_tiles.end(), [&](TileKey k){
      return !allowed.contains(k);
    });
    neighbor_tiles.erase(it, neighbor_tiles.end());

    //call all the callbacks
    for (auto callback : propagate_callbacks) {
      callback(neighbor_tiles, neighbor);
    }

    return neighbor_tiles.size() < initial_amount;
  }


  std::vector<Position> Solver::getNeighbors(Position p) {
    auto [x, y] = p;

    std::vector<Position> neighbors;

    if (0 < x) 
      neighbors.push_back({x-1, y});
    if (x < N-1)
      neighbors.push_back({x+1, y});
    if (0 < y) 
      neighbors.push_back({x, y-1});
    if (y < N-1)
      neighbors.push_back({x, y+1});

    return neighbors;
  }

  std::vector<TileKey>::const_iterator Solver::collapseRandom(const std::vector<TileKey>& tiles) {
    size_t index = rand() % tiles.size();
    return tiles.begin() + index;
  }

  std::unordered_set<TileKey> Solver::getAdjacencies(TileKey k, Direction d) {
    Side s{k, d};
    if (adjacency_constraints.contains(s)) {
      return adjacency_constraints[s];
    }
    //by default, every tile can be adjacent to every other tile
    std::unordered_set<TileKey> adjacencies(this->tiles.begin(), this->tiles.end());

    //caching, lazy initialization
    adjacency_constraints[s] = adjacencies;
    
    return adjacencies;
  }

  std::vector<TileKey> Solver::getPossibleTiles(Position p) {
    if (initial_constraints.contains(p)) {
      auto init = initial_constraints[p];

      std::vector<TileKey> possible_tiles;
      
      for (auto k : init) {
        possible_tiles.push_back(k);
      }
      
      return possible_tiles;
    }
    return this->tiles;
  }