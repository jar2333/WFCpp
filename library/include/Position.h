#pragma once

struct Position {
    int x;
    int y;
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
      return (k.y << 16 ) ^ k.x;
    }
  };

}