#include <string>
#include <Enums.h>
#include <BMPImage.h>
#include <memory>

#ifndef _TILE_h_
#define _TILE_h_
class Tile {

public:

    int getSize() const;
    std::shared_ptr<BMPImage> getImageData() const; 
    std::vector<Position> enumeratePosition() const;

private:

    int size;
    std::shared_ptr<BMPImage> image;
};

#endif
