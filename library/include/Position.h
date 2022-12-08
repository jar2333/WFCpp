#pragma once

#include <Direction.h>

#include <cstddef>

struct Position {
    size_t x;
    size_t y;

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
