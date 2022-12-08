#pragma once

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