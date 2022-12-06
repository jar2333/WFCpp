#pragma once

#include <vector>
#include <string>
#include <Position.h>
#include <FileType.h>
#include <sstream>

// 0~255
typedef unsigned char BYTE;

template<typename T> 
concept PixelType = requires
{
    T::Red; 
    T::Green; 
    T::Blue; 
    T::Alpha; 
};

typedef struct Pixel {
    int count;
	BYTE Blue;
	BYTE Green;
	BYTE Red;
	BYTE Alpha;

    template<PixelType T>
    Pixel& operator=(const T& rhs) {
        Alpha = rhs.Alpha;
        Blue = rhs.Blue;
        Green = rhs.Green;
        Red = rhs.Red;
        count = 0;
        return *this;
    }

} Pixel; 

inline bool operator==(const Pixel& lhs, const Pixel& rhs) { 
    return lhs.Pixel::Blue == rhs.Pixel::Blue && lhs.Pixel::Green == rhs.Pixel::Green && lhs.Red == rhs.Red;
}

std::ostream& operator<<(std::ostream &os, const Pixel &p);

constexpr Pixel defaultPixel = {
    0,
    255,
    255,
    255,
    0
};

constexpr int defaultHorizontalDPI = 96;
constexpr int defaultVerticalDPI = 96;
constexpr int defaultBitDepth = 32;

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

    void exportToFile(std::string filename, FileType type) const;

private:
    std::vector<std::vector<Pixel>> pixels;
    int bitDepth;
    int verticalDPI, horizontalDPI;

    inline bool checkPosition(Position pos) const;

};

inline bool operator==(const BMPImage& lhs, const BMPImage& rhs)
{
    if (lhs.getWidth() != rhs.getWidth() || lhs.getHeight() != rhs.getHeight()) {
        return false;
    }
    for (auto x = 0; x < lhs.getWidth(); x++)
        for (auto y = 0; y < lhs.getHeight(); y++) {
            if (lhs.getPixel({x, y}) != rhs.getPixel({x, y})) {
                return false;
            }
        }
    return true;
}

