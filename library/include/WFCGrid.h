#pragma once


class WFCGrid {

public:

    typedef int TileKey

    typedef typename std::function<TileKey(const std::vector<TileKey>&)> CollapseBehaviorT

    WFCGrid(int dimension) : tileMap(tileMap), dimension(dimension) {

    }

    int getDimension() {
        return dimension;
    }


    void collapseAt(Position p);


private:

    int dimension;

    CollapseBehaviorT collapse_behavior;

    std::vector<std::vector<std::vector<TileKey>>> tileKeyGrid;
    
};