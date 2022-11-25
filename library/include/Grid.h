#include <Tile.h>
#include <map>
#include <vector>

class Grid {

public:

    int getDimension();

    // TODO: replace (i, j) with Position
    Tile getPosition(int i, int j);
    void setPosition(int i, int j, Tile tile); // or: set(Position, TileKey)

private:

    int dimension;
    std::map<int, Tile> tileMap;
    std::vector<std::vector<int>> tileKeyGrid;

    // TODO: maybe some traverse helpers?
    
};
