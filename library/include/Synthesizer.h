#pragma once

#include <Tile.h>
#include <Grid.h>

#include <Solver.h>

#include <memory>

class Synthesizer {

public:

    Synthesizer() = default;
    ~Synthesizer() = default;

    void exportGridToFile(const Grid<Solver::TileKey>& grid, std::string exportPath);
    std::shared_ptr<BMPImage> exportGridToImage(const Grid<Solver::TileKey>& grid);
     
    void initRealTimeImage(unsigned int n);
    void modifyRealTimeImage(Position pos, const Tile* tile);
    std::shared_ptr<BMPImage> getRealTimeImage() const;
    void clearRealTimeImage();
    
    void exportRealTimeImageToFile(std::string exportPath);


private:

    std::shared_ptr<BMPImage> realTimeImage;
    void copyTileToGrid(Position pos, const Tile* tile, BMPImage* gridImage);

};
