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

#include <stdexcept>

#include <iostream>
#include <assert.h>

class Solver {
public:
  typedef size_t TileKey;

  typedef std::function<std::vector<TileKey>::const_iterator(const std::vector<TileKey>&)> CollapseBehavior;

  typedef std::function<void(const TileKey&, Position)> CollapseCallback;
  typedef std::function<void(const std::vector<TileKey>&, Position)> PropagateCallback;

  typedef typename std::list<CollapseCallback>::iterator CollapseCallbackCookie;
  typedef typename std::list<PropagateCallback>::iterator PropagateCallbackCookie;

  //the main way of using the library, the int keys are auto-generated from vector as the indeces
  template<typename T>
  Solver(const std::vector<T>& tiles, int seed=0): seed(seed) {
    for (TileKey k = 0; k < tiles.size(); k++) {
      this->tiles.push_back(k);
    }
  }

  //similar, but keys are provided explicitly for each tile
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
  void setSeed(int seed);
  int getSeed();
  
  Grid<TileKey> solve(int N);

  /*
   CONSTRAINT INTERFACE/API
   Set the solver constraints using this specified interface
  */

  /* Adjacency constraints */
  
  void addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);
  void removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);

  //using initializer list
  void addAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);
  void removeAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);

  /* Initial constraints */
  void setInitialConstraint(Position p, TileKey possibility);
  void setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities);
  
  /*
   CALLBACK INTERFACE/API
  */
 
  CollapseCallbackCookie registerOnCollapse(CollapseCallback callback);
  void deregisterOnCollapse(CollapseCallbackCookie cookie);

  PropagateCallbackCookie registerOnPropagate(PropagateCallback callback);
  void deregisterOnCollapse(PropagateCallbackCookie cookie);

  /*
   COLLAPSE INTERFACE
  */

  //low level access function to change collapse selection policy
  void setCollapseBehaviour(std::optional<CollapseBehavior> b);


private:
  typedef std::pair<TileKey, Direction> Side;

  int seed;
  std::vector<TileKey> tiles;

  /* CONSTRAINTS */
  std::map<Side, std::unordered_set<TileKey>> adjacency_constraints;
  std::unordered_map<Position, std::unordered_set<TileKey>> initial_constraints;

  /* BEHAVIOURS */
  CollapseBehavior collapse_behavior = nullptr;

  /* CALLBACKS */
  std::list<CollapseCallback> collapse_callbacks;
  std::list<PropagateCallback> propagate_callbacks;

  /* ALGORITHM */

  std::unordered_map<Position, std::vector<TileKey>> grid;
  int N;

  void initializeGrid(int N);
  void processInitialConstraints() ;
  void iterate();
  bool isCollapsed();
  bool isContradiction();
  Position getMinEntropyCoordinates();
  void collapseAt(Position p);
  void propagate(Position p);
  bool propagateAt(Position current, Position neighbor); //returns true if neighbor's possible tiles decrease
  std::vector<Position> getNeighbors(Position p);
  std::vector<TileKey>::const_iterator collapseRandom(const std::vector<TileKey>& tiles);
  std::unordered_set<TileKey> getAdjacencies(TileKey k, Direction d);
  std::vector<TileKey> getPossibleTiles(Position p);


};