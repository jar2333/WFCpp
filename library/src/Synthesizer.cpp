#include <BMPImage.h>
#include <Synthesizer.h>

#include <vector>
#include <memory>
#include <utility>

void Synthesizer::exportGridToFile(const Grid<Solver::TileKey>& grid, std::string exportPath, FileType type)
{
    auto resImage = exportGridToImage(grid);

    resImage->exportToFile(exportPath, type);
}

std::shared_ptr<BMPImage> Synthesizer::exportGridToImage(const Grid<Solver::TileKey>& grid)
{
    unsigned int gridDimension = grid.getDimension();
    unsigned int tileSize = grid.getTile(Position {0, 0})->getSize();

    auto resImage = std::make_shared<BMPImage>(gridDimension * tileSize, gridDimension * tileSize);

    for (auto pos : grid.enumeratePosition()) {
        auto tile = grid.getTile(pos);
        auto pixelPos = grid.translatePixelPosition(pos);
        
        copyTileToGrid(pixelPos, *tile, resImage.get());
    }

    return resImage;
}

void Synthesizer::initRealTimeImage(unsigned int n)
{
    if (realTimeImage != nullptr)
        clearRealTimeImage();
    realTimeImage = std::make_shared<BMPImage>(n, n);
}

std::shared_ptr<BMPImage> Synthesizer::getRealTimeImage() const
{
    return realTimeImage;
}

void Synthesizer::modifyRealTimeImage(Position pos, const Tile& tile)
{
    if (realTimeImage == nullptr)
        throw std::invalid_argument("realTimeImage not initialized. ");
    copyTileToGrid(pos, tile, realTimeImage.get());
}

void Synthesizer::exportRealTimeImageToFile(std::string exportPath, FileType type)
{
    realTimeImage->exportToFile(exportPath, type);
}

void Synthesizer::clearRealTimeImage()
{
    realTimeImage.reset();
    realTimeImage = nullptr;
}

void Synthesizer::copyTileToGrid(Position pos, const Tile& tile, BMPImage* gridImage)
{
    
    auto src = tile.getImageData();

    for (auto tilePos : tile.enumeratePosition()) {
            auto srcPixel = src->getPixel(tilePos);
            Position newPos = { pos.x + tilePos.x, pos.y + tilePos.y };
            gridImage->setPixel(newPos, srcPixel);
    }
}


