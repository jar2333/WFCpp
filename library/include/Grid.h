#pragma once

#include <Tile.h>
#include <Position.h>

#include <map>
#include <vector>

template <typename TileKey>
class Grid {

public:
    Grid() { dimension = 0; }

    ~Grid() = default;

    Grid(unsigned int dimension, std::map<TileKey, std::shared_ptr<Tile>> map)
    {
        setDimension(dimension);
        setTileMap(map);
    }
    
    Grid(unsigned int dimension)
    {
        setDimension(dimension);
    }

    unsigned int getDimension() const
    {
        return dimension;
    }

    void setDimension(unsigned int newDimension)
    {
        dimension = newDimension;
        tileKeyGrid.resize(newDimension, std::vector<TileKey>());
        for (auto& row : tileKeyGrid)
            row.resize(newDimension, TileKey(-1)); // suppose -1 == unassigned
    }

    TileKey getKey(Position p) 
    {
        return tileKeyGrid[p.x][p.y];
    }

    void setKey(Position p, TileKey key) 
    {
        setPosition(p, key);
    } 

    std::shared_ptr<Tile> getPosition(Position pos) const
    {
        if (!checkPosition(pos))
            throw std::out_of_range("Position out of range. ");
        
        auto tileKey = tileKeyGrid[pos.y][pos.x];
        auto tile = tileMap.at(tileKey);

        return tile;
    }

    void setPosition(Position pos, TileKey tileKey)
    {
        if (tileMap.find(tileKey) == tileMap.end())
            throw std::out_of_range("TileKey does not exist. ");

        if (!checkPosition(pos))
            throw std::out_of_range("Position out of range. ");

        tileKeyGrid[pos.y][pos.x] = tileKey;
    }

    void setTileMap(std::map<TileKey, std::shared_ptr<Tile>> newMap) {
        for(const auto & e : newMap)
        {
            // If the key exists, change only the value, add the {key, value} otherwise
            tileMap[e.first] = e.second;
        }
    }

    Position translatePixelPosition(Position pos) const
    {
        if (!checkPosition(pos))
            throw std::out_of_range("Position out of range. ");
        
        auto tileSize = getPosition({0, 0})->getSize();
        return {pos.x * tileSize, pos.y * tileSize};
    }

    std::vector<Position> enumeratePosition() const
    {
        std::vector<Position> res;

        for (int i = 0; i < dimension; i++)
            for (int j = 0; j < dimension; j++) {
                Position pos = {j, i};
                res.push_back(pos);
            }

        return res;
    }

private:

    unsigned int dimension;

    std::map<TileKey, std::shared_ptr<Tile>> tileMap;

    std::vector<std::vector<TileKey>> tileKeyGrid;

    constexpr bool checkPosition(Position pos) const
    {
        int i = pos.x;
        int j = pos.y;
        return (i < dimension && i >= 0 && j < dimension && j >= 0);
    }
};

