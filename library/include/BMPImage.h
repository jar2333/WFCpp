#pragma once

#include <vector>
#include <string>
#include <others.h>

// 0~255
typedef unsigned char  BYTE;

typedef struct Pixel {
    int count;
	BYTE Blue;
	BYTE Green;
	BYTE Red;
	BYTE Alpha;
} Pixel; 

constexpr Pixel defaultPixel = {
    0,
    255,
    255,
    255,
    0
};

class BMPImage {

public:

    BMPImage();
    BMPImage(unsigned int initWidth, unsigned int initHeight);
    BMPImage(std::string filename);
    ~BMPImage() = default;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setSize(unsigned int NewWidth , unsigned int NewHeight);

    Pixel getPixel(Position pos) const;
    void setPixel(Position pos, Pixel newPixel);

    void exportToBMPFile(std::string filename) const;
    void exportToPNGFile(std::string filename) const;

private:
    std::vector<std::vector<Pixel>> pixels;
    unsigned int width;
    unsigned int height;

    constexpr bool checkPosition(Position pos) const;
};
