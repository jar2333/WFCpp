#pragma once

#include <Tile.h>
#include <Position.h>

#include <map>
#include <vector>

template <typename TileKey>
class Grid {

public:

    Grid(const std::map<TileKey, Tile>& tileMap, int dimension) : tileMap(tileMap), dimension(dimension) {}

    int getDimension();

    inline TileKey getKey(Position p);
    inline void setKey(Position p, TileKey key); 

    inline Tile getTile(Position p);



private:

    int dimension;
    std::map<TileKey, Tile> tileMap;

    std::vector<std::vector<TileKey>> tileKeyGrid;

    // TODO: maybe some traverse helpers?
    
};