#pragma once

#include <Direction.h>

#include <cstddef>

/**
 * @brief The struct for storing grid coordinates. Overloads == operator in the usual manner.
 * 
 */
struct Position {
    size_t x;
    size_t y;

    /**
    * @brief A method for determining to what direction of the current Position any other Position is.
    *
    * @param other The other position
    * @return the direction from the current position that the other position is located in
    * @see Direction
    */
    Direction getDirection(Position other) {
      if (other.x > x)
        return Direction::RIGHT;
      else if (other.x < x)
        return Direction::LEFT;
      else if (other.y > y)
        return Direction::UP;
      else
        return Direction::DOWN;
    }
};

inline bool operator <(const Position& lhs, const Position& rhs){
    return lhs.x >= rhs.x ? lhs.y < rhs.y : true;
}

inline bool operator==(const Position& lhs, const Position& rhs) { 
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
