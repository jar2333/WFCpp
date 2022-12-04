#pragma once

#include <Direction.h>

struct Position {
    int x;
    int y;

    Direction getDirection(Position other) {
      auto x_offset = other.x - this->x;
      auto y_offset = other.y - this->y;  

      if (x_offset == 1)
        return Direction::RIGHT;
      else if (x_offset == -1)
        return Direction::LEFT;
      else if (y_offset == 1)
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

namespace std {

  template <>
  struct hash<Position> {
    std::size_t operator()(const Position& k) const {
      return (k.y << 16) ^ k.x;
    }
  };

}