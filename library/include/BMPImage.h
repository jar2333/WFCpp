#pragma once

#include <vector>
#include <string>
#include <Position.h>
#include <FileType.h>
#include <sstream>

/**
 * @brief The alias for number range from 0 to 255
 * 
 */
typedef unsigned char BYTE;

/**
 * @brief The concept for pixel-like objects.
 * It requires the type to contain RGBA properties/members.
 * 
 * @tparam T 
 */
template<typename T> 
concept PixelType = requires
{
    T::Red; 
    T::Green; 
    T::Blue; 
    T::Alpha; 
};

/**
 * @brief The struct for storing pixels in BMP. Supports up to 32-bit colors.
 * 
 */
typedef struct Pixel {
    int count;

    /**
     * @brief Blue value
     * 
     */
	BYTE Blue;

    /**
     * @brief Green value
     * 
     */
	BYTE Green;

    /**
     * @brief Red value
     * 
     */
	BYTE Red;

    /**
     * @brief Alpha value
     * 
     */
	BYTE Alpha;

    /**
     * @brief Overload the = operator to support assignment from pixel-like objects.
     * 
     * @tparam T 
     * @param rhs A pixel-like object
     * @return Pixel& 
     * 
     * @see PixelType
     */
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

/**
 * @brief Overload the == operator to support equal-comparison between Pixels.
 * The two Pixels are equal if their RGBA are all equal.
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */
inline bool operator==(const Pixel& lhs, const Pixel& rhs) { 
    return lhs.Pixel::Blue == rhs.Pixel::Blue && lhs.Pixel::Green == rhs.Pixel::Green && lhs.Red == rhs.Red && lhs.Alpha == rhs.Alpha;
}

/**
 * @brief Overload the << operator to support printing pixels with std::cout.
 * Example: std::cout << pixel << std::endl;
 * 
 * @param os 
 * @param p 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream &os, const Pixel &p);

/* DEFAULT CONSTANTS */

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

/**
 * @class BMPImage
 * @brief The BMPImage class
 * 
 * This class supports the import, export and basic modification of images as BMP files.
 * It provides an interface for image processing in @ref Extractor and @ref Synthesizer.
 * 
 * At the time, we only support png and bmp format images.
 * 
 * 
 */
class BMPImage {

public:

    /**
     * @brief Construct a new BMPImage object
     * 
     */
    BMPImage();

    /**
     * @brief Construct a new BMPImage object
     * 
     * @param initWidth 
     * @param initHeight 
     */
    BMPImage(unsigned int initWidth, unsigned int initHeight);

    /**
     * @brief Construct a new BMPImage object from image file.
     * 
     * @param filename File to read from. 
     */
    BMPImage(std::string filename);

    /**
     * @brief Destroy the BMPImage object
     * 
     */
    ~BMPImage() = default;


    /* Size */

    /**
     * @brief Get the width
     * 
     * @return the width as unsigned int
     */
    unsigned int getWidth() const noexcept;

    /**
     * @brief Get the height
     * 
     * @return the height as unsigned int 
     */
    unsigned int getHeight() const noexcept;

    /**
     * @brief Set the Size of the image. The added positions will be filled
     * with defaultPixel.
     * 
     * @param NewWidth 
     * @param NewHeight 
     */
    void setSize(unsigned int NewWidth , unsigned int NewHeight);

    /* Pixel */

    /**
     * @brief Get the Pixel object at some position
     * 
     * @param pos a position in image
     * @return Pixel 
     */
    Pixel getPixel(Position pos) const;

    /**
     * @brief Set the Pixel object at some position
     * 
     * @param pos a position in image
     * @param newPixel the new Pixel to be filled in
     * @throws std::out_of_range Indicates that the position is not valid. 
     */
    void setPixel(Position pos, Pixel newPixel);

    /**
     * @brief Export this object to a file of specified type.
     * 
     * @param filename The path for the exported image.
     * @param type The type of the image.
     * @throws std::runtime_error Indicates that the export fails.
     */
    void exportToFile(std::string filename, FileType type) const;

private:

    /* PIXELS */
    std::vector<std::vector<Pixel>> pixels;

    /* METADATA */
    int bitDepth;
    int verticalDPI, horizontalDPI;

    /* HELPERS */
    inline bool checkPosition(Position pos) const;

};

/**
 * @brief Overload the == operator to support equal-comparison between two images.
 * The two BMPImages are equal if their pixels are all equal.
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */
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

