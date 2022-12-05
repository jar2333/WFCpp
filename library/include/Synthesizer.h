#pragma once

#include <Grid.h>
#include <FileType.h>
#include <memory>


class Synthesizer {

public:

    Synthesizer() = default;
    ~Synthesizer() = default;

    void exportGridToFile(const Grid<TileKey>* grid, std::string exportPath, FileType type);
    std::shared_ptr<BMPImage> exportGridToImage(const Grid<TileKey>* grid);
     
    void initRealTimeImage(unsigned int n);
    void modifyRealTimeImage(Position pos, const Tile* tile);
    std::shared_ptr<BMPImage> getRealTimeImage() const;
    void clearRealTimeImage();
    
    void exportRealTimeImageToFile(std::string exportPath, FileType type);


private:

    std::shared_ptr<BMPImage> realTimeImage;
    void copyTileToGrid(Position pos, const Tile* tile, BMPImage* gridImage);

};
