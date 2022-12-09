#pragma once

#include <Direction.h>
#include <Position.h>
#include <BMPImage.h>

#include <string>
#include <memory>


/**
 * @class Tile
 * @brief The Tile class
 * 
 * This class is a wrapper for a BMPImage, to be used in the context of a @ref Grid and @ref Solver
 * 
 */
class Tile {

public:

    Tile() = default;
    ~Tile() = default;

    /**
    * @brief Constructor for initializing with image data
    * @throws ivalid_argument Image must be square
    */
    Tile(const std::shared_ptr<BMPImage> img)
    {
        if (img->getHeight() != img->getWidth())
            throw std::invalid_argument("Image must be square. ");
        size = img->getHeight();
        image = img;
    }

    /**
    * @brief Gets tile's size in pixels
    * @return the pixel size
    */
    unsigned int getSize() const
    {
        return size;
    }
    
    /**
    * @brief Gets tile's image data
    * 
    * @return the image data
    */
    std::shared_ptr<BMPImage> getImageData() const
    {
        return image;
    }

    /**
    * @brief Enumerates all positions in the image.
    * 
    * @return all pixel positions
    */
    std::vector<Position> enumeratePosition() const
    {
        std::vector<Position> res;

        for (unsigned int i = 0; i < size; i++)
            for (unsigned int j = 0; j < size; j++) {
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