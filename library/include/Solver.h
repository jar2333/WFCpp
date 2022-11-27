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

#include <cstdlib>

class Solver {

public:

  typedef Tile T;

  typedef int TileKey;

  typedef std::function<void(const T&, Position)> CollapseCallback;
  typedef std::function<void(const std::vector<T>&, Position)> PropagateCallback;

  typedef std::function<TileKey(std::vector<TileKey>&)> CollapseBehavior;

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
    initial_constraints[p].push_back(possibility);
  }

  void setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities) {
    initial_constraints[p].clear(); 
    for (auto k : possibilities) {
      initial_constraints[p].push_back(k);
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
  void setCollapseBehaviour(CollapseBehavior b) {
    collapse_behavior = b;
  }


private:
  int seed;

  std::map<TileKey, T> tiles;
  

  /*
   ALGORITHM (optimize)
  */
  std::map<Position, std::vector<TileKey>> grid;

  void initializeGrid(int N) {
    std::vector<TileKey> possible_tiles;
    for (auto const& [key, val] : tiles) {
      possible_tiles.push_back(key);
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        grid[{i, j}] = possible_tiles;
      }
    }
  }

  TileKey collapseAt(std::vector<TileKey>& tiles) {
    if (this->collapse_behavior) {
      return collapse_behavior.value()(tiles);
    }
    return collapseRandom(tiles);
  }

  TileKey collapseRandom(std::vector<TileKey>& tiles) {
    int index = rand() % tiles.size();

    auto key = tiles[index];

    tiles.erase(tiles.begin() + index);

    return key;
  }

  /*
    BEHAVIOURS
  */
  std::optional<CollapseBehavior> collapse_behavior = {};

  /*
   CONSTRAINTS
  */
  std::map<std::pair<TileKey, Direction>, std::unordered_set<TileKey>> adjacency_constraints;
  std::map<Position, std::vector<TileKey>> initial_constraints;


  /*
    CALLBACKS
  */
  std::list<CollapseCallback> collapse_callbacks;
  std::list<PropagateCallback> propagate_callbacks;
};