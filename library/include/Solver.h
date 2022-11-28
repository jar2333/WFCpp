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

#include <utility>
#include <tuple>

#include <optional>

#include <iterator>

#include <algorithm>

#include <cstdlib>

class Solver {

public:

  typedef Tile T;
  typedef int TileKey;

  typedef std::pair<TileKey, Direction> Side;

  typedef std::function<std::vector<TileKey>::const_iterator(const std::vector<TileKey>&)> CollapseBehavior;

  typedef std::function<void(const T&, Position)> CollapseCallback;
  typedef std::function<void(const std::vector<T>&, Position)> PropagateCallback;

  typedef typename std::list<CollapseCallback>::iterator CollapseCallbackCookie;
  typedef typename std::list<PropagateCallback>::iterator PropagateCallbackCookie;

  //the main way of using the library, the int keys are auto-generated from vector as the indeces
  Solver(const std::vector<T>& tiles, int seed=0): seed(seed) {
    for (TileKey k = 0; k < tiles.size(); k++) {
      this->tiles[k] = tiles[k];
    }
  }

  //similar, but keys are provided explicitly for each tile
  Solver(const std::map<TileKey, T>& tiles, int seed=0): seed(seed) {
    this->tiles = tiles;
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

  Grid<T> solve(int N); 

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
  CollapseCallbackCookie registerCollapse(CollapseCallback callback) {
    return collapse_callbacks.insert(collapse_callbacks.begin(), callback);
  }

  void deregisterCollapse(CollapseCallbackCookie cookie) {
    collapse_callbacks.erase(cookie);
  }


  //API: calls registered function with possible tiles in collapsed grid slot
  PropagateCallbackCookie registerPropagate(PropagateCallback callback) {
    return propagate_callbacks.insert(propagate_callbacks.begin(), callback);
  }

  void deregisterCollapse(PropagateCallbackCookie cookie) {
    propagate_callbacks.erase(cookie);
  }


  /*
   HEURISTIC INTERFACE
  */

  // Low level function to change the position selection heuristic
  // A comparison function, during propagation, run to find the global minimum tile to collapse
  // Write details in documentation
  // void setSelectionHeuristic(std::function<bool(const std::vector&<TileKey>, const std::vector&<TileKey>)> h)

  //low level function to change collapse selection policy
  void setCollapseBehaviour(std::optional<CollapseBehavior> b) {
    if (!b) {
      collapse_behavior = nullptr;
    }
    collapse_behavior = b.value();
  }


private:
  int seed;
  std::map<TileKey, T> tiles;

  /*
    CONSTRAINTS
  */
  std::map<Side, std::unordered_set<TileKey>> adjacency_constraints;
  std::map<Position, std::unordered_set<TileKey>> initial_constraints;

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
  Position nextToCollapse;

  Position getMinEntropyCoordinates() {
    return nextToCollapse;
  }

  void initializeGrid(int N) {
    //get vector of all possible tiles
    std::vector<TileKey> max_tiles;
    for (auto const& [tile_key, _] : tiles) {
      max_tiles.push_back(tile_key);
    }

    //populate grid
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        Position p{i, j};
        initializeGridPosition(p, max_tiles);
      }
    }
  }

  void initializeGridPosition(Position p, std::vector<TileKey>& max_tiles) {
    grid[p] = [&](){
      if (initial_constraints.contains(p)) {
        auto init = initial_constraints[p];

        std::vector<TileKey> possible_tiles;
        std::copy_if(max_tiles.begin(), max_tiles.end(), std::back_inserter(possible_tiles), [&](TileKey k){
          return init.contains(k);
        });
        
        return possible_tiles;
      }
      return max_tiles;
    }();
  }

  void collapseAt(std::vector<TileKey>& tiles) {
    auto it = [&](){
      if (collapse_behavior) {
        return collapse_behavior(tiles);
      }
      return collapseRandom(tiles);
    }();

    TileKey tile = *it;
    tiles.clear();
    tiles.push_back(tile);
  }

  std::vector<TileKey>::const_iterator collapseRandom(const std::vector<TileKey>& tiles) {
    size_t index = rand() % tiles.size();
    return tiles.begin() + index;
  }

};