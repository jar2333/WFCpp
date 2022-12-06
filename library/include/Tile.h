#pragma once

#include <Direction.h>
#include <Position.h>
#include <BMPImage.h>

#include <string>
#include <memory>

class Tile {

public:

    Tile() = default;
    ~Tile() = default;

    Tile(const std::shared_ptr<BMPImage> img)
    {
        if (img->getHeight() != img->getWidth())
            throw std::invalid_argument("Image must be square. ");
        size = img->getHeight();
        image = img;
    }

    unsigned int getSize() const
    {
        return size;
    }
    
    std::shared_ptr<BMPImage> getImageData() const
    {
        return image;
    }

    std::vector<Position> enumeratePosition() const
    {
        std::vector<Position> res;

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++) {
                Position pos = {j, i};
                res.push_back(pos);
            }

        return res;
    }

private:

    std::string filePath;
    // TODO: add other variables

    unsigned int size;
    std::shared_ptr<BMPImage> image;
};