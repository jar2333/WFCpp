#pragma once

#include <Tile.h>
#include <Grid.h>
#include <Position.h>

#include <map>
#include <set>
#include <vector>
#include <list>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <stack>

#include <utility>
#include <tuple>

#include <optional>

#include <iterator>

#include <algorithm>

#include <cstdlib>

class Solver {


public:

  typedef int TileKey;

  typedef std::pair<TileKey, Direction> Side;

  typedef std::function<std::vector<TileKey>::const_iterator(const std::vector<TileKey>&)> CollapseBehavior;

  typedef std::function<void(const TileKey&, Position)> CollapseCallback;
  typedef std::function<void(const std::vector<TileKey>&, Position)> PropagateCallback;

  typedef typename std::list<CollapseCallback>::iterator CollapseCallbackCookie;
  typedef typename std::list<PropagateCallback>::iterator PropagateCallbackCookie;

  //the main way of using the library, the int keys are auto-generated from vector as the indeces
  //can be templated!!!!
  template<typename T>
  Solver(const std::vector<T>& tiles, int seed=0): seed(seed) {
    for (TileKey k = 0; k < tiles.size(); k++) {
      this->tiles.push_back(k);
    }
  }

  //similar, but keys are provided explicitly for each tile
  //can be templated!!!!
  template<typename T>
  Solver(const std::map<TileKey, T>& tiles, int seed=0): seed(seed) {
    for (auto [k, _] : tiles) {
      this->tiles.push_back(k);
    }
  }

  /*
   SOLVER API
  */

  //change seed whenever
  void setSeed(int seed) {
    seed = seed;
    srand(seed);
  }

  int getSeed() {
    return seed;
  }

  Grid<TileKey> solve(int N); 

  /*
   CONSTRAINT INTERFACE/API
  */

  /* Adjacency constraints */
  //set the constraints using this specified interface
  void addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor) {
    adjacency_constraints[std::make_pair(t, d)].insert(neighbor);
  }

  void removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor) {
    adjacency_constraints[std::make_pair(t, d)].erase(neighbor);
  }

  //using initializer list
  void addAdjacencyConstraints(TileKey t, Direction d, std::initializer_list<TileKey> neighbors) {
    auto p = std::make_pair(t, d);
    for (auto n : neighbors) {
      adjacency_constraints[p].insert(n);
    }
  }

  void removeAdjacencyConstraints(TileKey t, Direction d, std::initializer_list<TileKey> neighbors) {
    auto p = std::make_pair(t, d);
    for (auto n : neighbors) {
      adjacency_constraints[p].erase(n);
    }
  }

  /* Initial constraints */
  void setInitialConstraint(Position p, TileKey possibility) {
    initial_constraints[p].clear();
    initial_constraints[p].insert(possibility);
  }

  void setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities) {
    initial_constraints[p].clear(); 
    for (auto k : possibilities) {
      initial_constraints[p].insert(k);
    }
  }
  
  /*
   CALLBACK INTERFACE/API
  */
 
  //To-do: returns a receipt object to deregister when out of scope?
  //API: calls registered function with tile in collapsed grid slot
  // vector<int> tiles;
  // Solver solver(tiles);
  // solver.registerOnCollapse([&](const int& key, Position p) {
  //   tile = tiles[key];
  //   auto [x, y] = p;
  //   opengl.draw(tile, x, y);
  // });

  CollapseCallbackCookie registerOnCollapse(CollapseCallback callback) {
    return collapse_callbacks.insert(collapse_callbacks.begin(), callback);
  }

  void deregisterOnCollapse(CollapseCallbackCookie cookie) {
    collapse_callbacks.erase(cookie);
  }


  //API: calls registered function with possible tiles in collapsed grid slot
  PropagateCallbackCookie registerOnPropagate(PropagateCallback callback) {
    return propagate_callbacks.insert(propagate_callbacks.begin(), callback);
  }

  void deregisterOnCollapse(PropagateCallbackCookie cookie) {
    propagate_callbacks.erase(cookie);
  }


  /*
   HEURISTIC INTERFACE
  */

  // Low level function to change the position selection heuristic
  // A comparison function, during propagation, run to find the global minimum tile to collapse
  // Write details in documentation

  //low level function to change collapse selection policy
  void setCollapseBehaviour(std::optional<CollapseBehavior> b) {
    if (!b) {
      collapse_behavior = nullptr;
    }
    collapse_behavior = b.value();
  }


private:
  int seed;
  std::vector<TileKey> tiles;

  /*
    CONSTRAINTS
  */
  std::map<Side, std::unordered_set<TileKey>> adjacency_constraints;
  std::unordered_map<Position, std::unordered_set<TileKey>> initial_constraints;

  /*
    BEHAVIOURS
  */
  CollapseBehavior collapse_behavior = nullptr;

  /*
    CALLBACKS
  */
  std::list<CollapseCallback> collapse_callbacks;
  std::list<PropagateCallback> propagate_callbacks;

  /*
    ALGORITHM (optimize)
  */

  std::unordered_map<Position, std::vector<TileKey>> grid;
  int N;

  void initializeGrid(int N) {
    grid.clear();

    this->N = N;

    //populate grid
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        Position p{i, j};
        grid[p] = getPossibleTiles(p);;
      }
    }
  }

  std::vector<TileKey> getPossibleTiles(Position p) {
    if (initial_constraints.contains(p)) {
      auto init = initial_constraints[p];

      std::vector<TileKey> possible_tiles;
      std::copy_if(this->tiles.begin(), this->tiles.end(), std::back_inserter(possible_tiles), [&init](TileKey k){
        return init.contains(k);
      });
      
      return possible_tiles;
    }
    return this->tiles;
  }

  void iterate() {
    Position p = getMinEntropyCoordinates();
    collapseAt(p);
    propagate(p);
  }

  //optimizations can be made using an instance variable
  bool isCollapsed() {
    for (const auto& [p, t] : this->grid) {
      if (t.size() != 1)
        return false;
    }
    return true;
  }

  //alternatively make this an exception?
  bool isContradiction() {
    for (const auto& [p, t] : this->grid) {
      if (t.size() == 0)
        return true;
    }
    return false;
  }

  Position getMinEntropyCoordinates() {
    Position min_entropy_position;
    size_t min_entropy = tiles.size();
    for (auto const [p, v] : grid) {
      if (v.size() < min_entropy) {
        min_entropy_position = p;
        min_entropy = v.size();
      }
    }
    return min_entropy_position;
  }

  void collapseAt(Position p) {
    std::vector<TileKey>& tiles = grid[p];

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

  void propagate(Position p) {
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
  bool propagateAt(Position current, Position neighbor) {
    std::vector<TileKey>& neighbor_tiles = grid[neighbor];
    size_t initial_amount = neighbor_tiles.size();

    std::vector<TileKey>& current_tiles = grid[current];

    Direction d = current.getDirection(neighbor);
    
    //for each tile in the current grid slot, check its set of allowed neighbors in the given direction
    //add that to an overall set of permitted tiles, which is then used to remove any which are not in this set
    std::unordered_set<TileKey> allowed;
    for (TileKey k : current_tiles) {
      auto adjacencies = getAdjacencies(k, d);
      for (TileKey a : adjacencies) {
        allowed.insert(a);
      }
    }

    std::remove_if(neighbor_tiles.begin(), neighbor_tiles.end(), [&](TileKey k){
      return !allowed.contains(k);
    });

    //call all the callbacks
    for (auto callback : propagate_callbacks) {
      callback(neighbor_tiles, neighbor);
    }

    return neighbor_tiles.size() < initial_amount;
  }


  std::vector<Position> getNeighbors(Position p) {
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

  std::vector<TileKey>::const_iterator collapseRandom(const std::vector<TileKey>& tiles) {
    size_t index = rand() % tiles.size();
    return tiles.begin() + index;
  }

  std::unordered_set<TileKey> getAdjacencies(TileKey k, Direction d) {
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

};