#include <Tile.h>
#include <others.h>
#include <map>
#include <vector>

#ifndef _GRID_h_
#define _GRID_h_

class Grid {

public:

    Grid() = default;
    ~Grid() = default;

    unsigned int getDimension() const;

    std::shared_ptr<Tile> getPosition(Position pos) const;
    void setPosition(Position t, Tile tile); // or: set(Position, TileKey)
    Position translatePixelPosition(Position pos) const;

    std::vector<Position> enumeratePosition() const;

private:

    unsigned int dimension;
    std::map<int, Tile> tileMap;
    std::vector<std::vector<int>> tileKeyGrid;
    
    // TODO: maybe some traverse helpers?
    
};

#endif
