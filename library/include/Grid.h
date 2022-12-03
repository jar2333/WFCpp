#pragma once

#include <Tile.h>
#include <Position.h>

#include <map>
#include <vector>

template <typename TileKey>
class Grid {

public:

    Grid(const std::vector<TileKey>& tileKeys, int dimension) : tileKeys(tileKeys), dimension(dimension) {
        for (int i = 0; i < dimension; i++) {
            std::vector<TileKey> row(dimension);
            for (int j = 0; j < dimension; j++) {
                tileKeyGrid.push_back(row);
            }
        }
    }
    // Grid(const std::vector<TileKey>& tileKeys, int dimension) : tileKeys(tileKeys), dimension(dimension) {}
    // Grid(const std::map<TileKey, Tile>& tileMap, int dimension) : tileMap(tileMap), dimension(dimension) {}

    int getDimension() {
        return this->dimension;
    }

    TileKey getKey(Position p) {
        auto [x, y] = p;
        return tileKeyGrid[x][y];
    }

    void setKey(Position p, TileKey key) {
        auto [x, y] = p;
        tileKeyGrid[x][y] = key;
    } 

    // Tile getTile(Position p);



private:

    int dimension;
    std::vector<TileKey> tileKeys;
    // std::map<TileKey, Tile> tileMap;

    std::vector<std::vector<TileKey>> tileKeyGrid;

    // TODO: maybe some traverse helpers?
    
};