#pragma once

#include <Tile.h>
#include <map>
#include <vector>

template <typename TileKey>
class Grid {

public:

    Grid(std::map<TileKey, Tile> tileMap, int dimension) : tileMap(tileMap), dimension(dimension) {}

    int getDimension();

    // TODO: replace (i, j) with Position
    TileKey getPosition(int i, int j);
    Tile getPositionTile(int i, int j);

    void setPosition(int i, int j, TileKey tile); // or: set(Position, TileKey)


private:

    int dimension;
    std::map<TileKey, Tile> tileMap;

    std::vector<std::vector<TileKey>> tileKeyGrid;

    // TODO: maybe some traverse helpers?
    
};