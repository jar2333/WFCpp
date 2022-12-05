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

namespace std {
  template <>
  struct hash<Position> {
    std::size_t operator()(const Position& k) const {
      return (k.y << 16) ^ k.x;
    }
  };
}

/**
* @class Solver
* @brief The Solver class
* @author Jose A. Ramos
*
* This class implements the Wave Function Collapse (WFC) algorithm. 
* It provides an interface for calling the algorithm, for setting
* the solver constraints, changing some algorithm behavior, and registering
* for certain events. It utilizes keys to represent tiles, returning a 2D grid of keys.
*
* At the moment, only 2 dimensional square grids are available to be solved by the algorithm.
* This limitation is not hard to overcome, and in fact this class can be generalized with minor
* changes to some key private methods and the @ref Direction enum. 
* 
* The algorithm consists of a grid, with each slot/square having a set of allowed tiles at any
* given time. In the WFC literature, this is called a "superposition", although we avoid that nomenclature.
* A grid square is said to be "collapsed" when only one tile is allowed in it. The grid itself is said to
* be "collapsed" when all of its squares are collapsed. This constitutes a "solved" grid. If a grid square
* ever has zero allowed tiles, that means the grid is in "contradiction". A solution cannot be found from a 
* contradiction.
*
* WFC works by iterating 3 steps until either the grid is solved or a leads to a contradiction:
*   - Find the non-collapsed grid square with the least number of allowed tiles (this is the "min entropy heuristic").
*   - Collapse the grid square using some policy (usually uniform random sampling).
*   - Propagate the results of the new collapsed grid square, removing tiles that are now disallowed by adjacency constraints.
* 
* Beyond offering the solve method, this class provides an API to define <i>adjacency constraints</i> and 
* <i>initial constraints</i>, which guide the final solution to the grid. Additionally, it provides an API for 
* registering functions to be called on the information at a grid square whenever it either collapses or is 
* affected by propagation. Finally, an API is provided for changing the way grid squares are collapsed.
*
* @see Grid
* @see Direction
* @see Position
*/
class Solver {
public:

  /**
  * The alias for the key type used for tiles in the algorithm.
  */
  typedef size_t TileKey;

  typedef std::function<std::vector<TileKey>::const_iterator(const std::vector<TileKey>&)> CollapseBehavior;

  typedef std::function<void(const TileKey&, Position)> CollapseCallback;
  typedef std::function<void(const std::vector<TileKey>&, Position)> PropagateCallback;

  /**
  * The alias for the callback cookie type for collapse events
  * @see registerOnCollapse(CollapseCallback callback)
  */
  typedef typename std::list<CollapseCallback>::iterator CollapseCallbackCookie;

  /**
  * The alias for the callback cookie type for propagation events
  * @see registerOnPropagate(PropagateCallback callback)
  */
  typedef typename std::list<PropagateCallback>::iterator PropagateCallbackCookie;

  /**
  * The tile keys are auto-generated from vector as the indeces.
  * @param tiles A vector of tiles.
  * @param seed The seed for the random number generator.
  */
  template<typename T>
  Solver(const std::vector<T>& tiles, int seed=0): seed(seed) {
    for (TileKey k = 0; k < tiles.size(); k++) {
      this->tiles.push_back(k);
    }
  }

  /**
  * Keeps track of tile keys from a given mapping of tile keys to tiles.
  * @param tiles A map of tile keys to tiles.
  * @param seed The seed for the random number generator.
  */
  template<typename T>
  Solver(const std::map<TileKey, T>& tiles, int seed=0): seed(seed) {
    for (auto [k, _] : tiles) {
      this->tiles.push_back(k);
    }
  }

  /*
   SOLVER API
  */

  /**
  * @brief Set the seed for the random number generator. 
  * @param seed the seed
  */
  void setSeed(int seed);

  /**
  * @brief Get the seed for the random number generator. 
  * @return the seed
  */
  int getSeed();
  
  /**
  * Runs the wave-function collapse algorithm, returning a solved 2-dimensional square Grid or throwing an exception if the algorithm fails.
  * The grid returned is of dimensions NxN.
  * @param N The dimensions of the square grid. 
  * @return A solved grid
  * @throws std::runtime_error Indicates that the grid could not be solved. 
  */
  Grid<TileKey> solve(int N);

  /*
   CONSTRAINT INTERFACE/API
   Set the solver constraints using this specified interface
  */

  /**
  * A method for adding an <it>adjacency constraint</it>. An adjacency constraint
  * consists of a given tile, a direction, and a neighbor tile. The constraint specifies that
  * the neighbor tile is allowed to be adjacent to the given tile in said direction. Inversely, if
  * such a constraint does not exist, the neighbor tile is not allowed to be adjacent in that direction.
  * 
  * By default, if <b>no</b> constraint exists for a (tile, direction) pair, every tile is allowed
  * to be adjacent to the given tile in that direction. This is why they are called <it>constraints</it>,
  * since it constrains this default case by only allowing specific neighbors.
  *
  * This method is idempotent.
  *
  * @param t The tile key which will have a new possible neighbor
  * @param d The direction in which the neighbor will be possible
  * @param neighbor The tile key which is allowed to be adjacent to t in direction d
  */  
  void addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);

  /**
  * A method for removing an <it>adjacency constraint</it>. 
  *
  * This method is idempotent.
  *
  * @see Solver::addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor)
  * @param t The tile key which will have a possible neighbor removed
  * @param d The direction in which the neighbor will no longer be a possible
  * @param neighbor The tile key which is no longer allowed to be adjacent to t in direction d
  */
  void removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor);

  /**
  * A multi-argument version of @ref Solver::addAdjacencyConstraint
  * Utilizes an initializer list, for use by programmers.
  *
  * This method is idempotent.
  *
  * @see Solver::addAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor)
  * @param t The tile key which will have a new possible neighbor
  * @param d The direction in which the neighbor will be possible
  * @param neighbors The tile keys which are allowed to be adjacent to t in direction d
  */  
  void addAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);

  /**
  * A multi-argument version of @ref Solver::addAdjacencyConstraint
  * Utilizes an initializer list, for use by programmers.
  *
  * This method is idempotent.
  *
  * @see Solver::removeAdjacencyConstraint(TileKey t, Direction d, TileKey neighbor)
  * @param t The tile key which will have a possible neighbor removed
  * @param d The direction in which the neighbor will no longer be a possible
  * @param neighbors The tile keys which are no longer allowed to be adjacent to t in direction d
  */
  void removeAdjacencyConstraint(TileKey t, Direction d, std::initializer_list<TileKey> neighbors);

  /**
  * A method to set an <it>initial constraint</it>. An initial constraint involves a grid position
  * and a tile key. The grid square at the given position is preemptively collapsed to the given tile key,
  * with the results being propagated, before the algorithm begins. This gives the user more say in the
  * kinds of solutions that the algorithm will reach. 
  *
  * Liberal use of initial constraints may lead to frequent contradictions, so limiting their use is adviced. 
  *
  * Unlike the adjacency constraint API, succesive calls to this method with the same position but different tile keys
  * does not add them all to the grid position. It is a setter, not an inserter.
  *
  * @param p the grid position for the initial constraint
  * @param possibility the sole tile key which will be allowed in this grid position 
  */
  void setInitialConstraint(Position p, TileKey possibility);

  /**
  * A multi-tile version of @ref setInitialConstraint(Position p, TileKey possibility)
  *
  * If an empty initializer list is passed, nothing will occur. 
  *
  * @param p the grid position for the initial constraint
  * @param possibilities the tile keys which will be allowed in this grid position 
  */
  void setInitialConstraint(Position p, std::initializer_list<TileKey> possibilities);
  
  /*
   CALLBACK INTERFACE/API
  */
 
  /**
  * Registers a function to be called whenever a grid square collapses. 
  * The function argument is the tile key now occupying that grid square, and the position.
  * Returns a cookie to allow deregistering the function later.
  * 
  * @see CollapseCallback
  * @see CollapseCallbackCookie
  * @see deregisterOnCollapse(CollapseCallbackCookie cookie)
  * @param callback a function to be called when a grid square collapses
  * @return a cookie to be used for deregistering the callback
  */
  CollapseCallbackCookie registerOnCollapse(CollapseCallback callback);

  /**
  * Deregisters a function that is called whenever a grid square collapses. 
  * 
  * @see CollapseCallbackCookie
  * @see registerOnCollapse(CollapseCallback callback)
  * @param cookie a cookie used to indentify and remove a callback
  */
  void deregisterOnCollapse(CollapseCallbackCookie cookie);

  /**
  * Registers a function to be called whenever a grid square collapses. 
  * The function argument is the tile key now occupying that grid square, and the position.
  * Returns a cookie to allow deregistering the function later.
  * 
  * @see PropagateCallback
  * @see PropagateCallbackCookie
  * @see deregisterOnCollapse(PropagateCallbackCookie cookie)
  * @param callback a function to be called when a grid square is interacted with during constraint propagation. 
  * @return a cookie to be used for deregistering the callback
  */
  PropagateCallbackCookie registerOnPropagate(PropagateCallback callback);

  /**
  * Deregisters a function that is called whenever a grid square is interacted with during constraint propagation. 
  * 
  * @see PropagateCallbackCookie
  * @see registerOnPropagate(PropagateCallback callback)
  * @param cookie a cookie used to indentify and remove a callback
  */
  void deregisterOnCollapse(PropagateCallbackCookie cookie);

  /*
   COLLAPSE INTERFACE
  */

  /**
  * Low level access function to change selection policy used in collapse.
  * Can be set to a null value, in which case @ref collapseRandom is used instead.
  * 
  * @see CollapseBehavior
  * @param b a function which returns an iterator to a specific tile key in a grid square
  */
  void setCollapseBehaviour(std::optional<CollapseBehavior> b);


private:
  typedef std::pair<TileKey, Direction> Side;

  /* INITIAL */
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

