#pragma once

#include <Tile.h>
#include <Position.h>

#include <map>
#include <vector>
#include <limits.h>

template <typename TileKey>
class Grid {

public:
    Grid() { dimension = 0; }

    ~Grid() = default;

    Grid(size_t dimension, std::map<TileKey, std::shared_ptr<Tile>> map)
    {
        setDimension(dimension);
        setTileMap(map);
    }
    
    Grid(size_t dimension)
    {
        setDimension(dimension);
    }

    size_t getDimension() const
    {
        return dimension;
    }

    void setDimension(size_t newDimension)
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
        if (!checkPosition(p))
            throw std::out_of_range("Position out of range. ");

        tileKeyGrid[p.y][p.x] = key;
    } 

    std::shared_ptr<Tile> getTile(Position pos) const
    {
        if (!checkPosition(pos))
            throw std::out_of_range("Position out of range. ");
        
        auto tileKey = tileKeyGrid[pos.y][pos.x];
        auto tile = tileMap.at(tileKey);

        return tile;
    }

    void setTile(Position pos, TileKey tileKey)
    {
        if (!tileMap.contains(tileKey))
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

        if (getTile(pos)->getSize() > INT_MAX)
            throw std::runtime_error("Tile size too big. ");
        
        auto tileSize = getTile(pos)->getSize();
        
        return { pos.x * tileSize, pos.y * tileSize} ;
    }

    std::vector<Position> enumeratePosition() const
    {
        std::vector<Position> res;

        for (size_t i = 0; i < dimension; i++)
            for (size_t j = 0; j < dimension; j++) {
                Position pos = {j, i};
                res.push_back(pos);
            }

        return res;
    }

private:

    size_t dimension;

    std::map<TileKey, std::shared_ptr<Tile>> tileMap;

    std::vector<std::vector<TileKey>> tileKeyGrid;

    constexpr bool checkPosition(Position pos) const
    {
        size_t i = pos.x;
        size_t j = pos.y;
        return (i < dimension && i >= 0 && j < dimension && j >= 0);
    }
};

