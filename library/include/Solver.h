#pragma once

#include <Tile.h>
#include <Grid.h>
#include <Position.h>

#include <map>
#include <vector>
#include <list>
#include <functional>
#include <unordered_set>
#include <unordered_map>

#include <utility>

class Solver {

public:

  typedef Tile T;

  typedef typename int TileKey;

  typedef std::function<void(const T&, Position)> CollapseCallbackT;
  typedef std::function<void(const std::vector<T>&, Position)> PropagateCallbackT;  

  typedef typename std::list<CollapseCallbackT>::iterator CollapseCallbackCookie;
  typedef typename std::list<PropagateCallbackT>::iterator PropagateCallbackCookie;

  //the main way of using the library, the int keys are auto-generated from vector as the indeces
  Solver(const std::vector<T>& tiles, int seed=0) {
    for (TileKey k = 0; k < tiles.size(); k++) {
      this->tiles[k] = tiles[k];
    }
  }

  //similar, but keys are provided explicitly for each tile
  Solver(const std::map<TileKey, T>& tiles, int seed=0) {
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
  void addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);
  void removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);

  //using initializer list
  void addAdjacencyConstraints(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);
  void removeAdjacencyConstraints(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);

  /* Initial constraints */
  void setInitialConstraint(Position p, TileKey possibility);
  void setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities);
  
  /*
   CALLBACK INTERFACE/API
  */
 
  //To-do: returns a receipt object to deregister when out of scope?
  //API: calls registered function with tile in collapsed grid slot
  CollapseCallbackCookie registerCollapse(std::function<void(const T&, Position)> callback) {
    return collapse_callbacks.insert(collapse_callbacks.begin(), callback);
  }

  void deregisterCollapse(CollapseCallbackCookie cookie) {
    return collapse_callbacks.erase(cookie);
  }


  //API: calls registered function with possible tiles in collapsed grid slot
  PropagateCallbackCookie registerPropagate(std::function<void(const std::vector<T>&, Position)> callback) {
    return propagate_callbacks.insert(collapse_callbacks.begin(), callback);
  }

  void deregisterCollapse(PropagateCallbackCookie cookie) {
    return propagate_callbacks.erase(cookie);
  }


  /*
   HEURISTIC INTERFACE
  */

  // Low level function to change the position selection heuristic
  // A comparison function, during propagation, run to find the global minimum tile to collapse
  // Write details in documentation
  // void setSelectionHeuristic(std::function<bool(const std::vector&<TileKey>, const std::vector&<TileKey>)> h)

  //low level function to change collapse selection policy
  // void setCollapseBehaviour(std::function<TileKey(const std::vector&<TileKey>)> b);


private:
  int seed;

  std::map<TileKey, T> tiles;
  //  std::function<TileKey(std::vector&<TileKey>)> heuristic;

  std::unordered_map<std::pair<TileKey, Direction>, std::unordered_set<TileKey>> adjacency_constraints;

  std::list<CollapseCallbackT> collapse_callbacks;
  std::list<PropagateCallbackT> propagate_callbacks;
};