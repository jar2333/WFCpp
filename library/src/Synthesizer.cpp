#include <vector>
#include <memory>
#include <utility>
#include <BMPImage.h>
#include <Synthesizer.h>

void Synthesizer::exportGridToFile(const Grid* grid, std::string exportPath)
{

    auto resImage = exportGridToImage(grid);

    return resImage->exportToPNGFile(exportPath);

}

std::shared_ptr<BMPImage> Synthesizer::exportGridToImage(const Grid* grid)
{
    unsigned int gridDimension = grid->getDimension();
    unsigned int tileSize = grid->getPosition(Position {0, 0})->getSize();

    auto resImage = std::make_shared<BMPImage>(gridDimension * tileSize, gridDimension * tileSize);

    for (auto pos : grid->enumeratePosition()) {
        auto tile = grid->getPosition(pos);
        auto pixelPos = grid->translatePixelPosition(pos);

        copyTileToGrid(pixelPos, tile.get(), resImage.get());
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

void Synthesizer::modifyRealTimeImage(Position pos, const Tile* tile)
{
    if (realTimeImage == nullptr)
        throw std::runtime_error("realTimeImage not initialized. ");
    copyTileToGrid(pos, tile, realTimeImage.get());
}

void Synthesizer::exportRealTimeImageToFile(std::string exportPath)
{
    realTimeImage->exportToPNGFile(exportPath);
}

void Synthesizer::clearRealTimeImage()
{
    realTimeImage.reset();
    realTimeImage = nullptr;
}

void Synthesizer::copyTileToGrid(Position pos, const Tile* tile, BMPImage* gridImage)
{
    
    auto src = tile->getImageData();
    auto height = src->getHeight();
    auto width = src->getWidth();

    for (auto tilePos : tile->enumeratePosition()) {
            auto srcPixel = src->getPixel(pos);
            Position newPos = { pos.x + tilePos.x, pos.y + tilePos.y };
            gridImage->setPixel(newPos, srcPixel);
    }
}


