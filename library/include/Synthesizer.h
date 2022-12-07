#pragma once

#include <Solver.h>
#include <FileType.h>
#include <memory>


/**
* @class Synthesizer
* @brief The Synthesizer class
*
* This class implements the functionality of synthesizing grid into an out put image.
* At the moment, only png and bmp images are supported. 
* All generated images are stored as @ref BMPImage and transformed into specified format.
*
* @see Grid
* @see BMPImage
*/
class Synthesizer {

public:

    /**
     * @brief Construct a new Synthesizer object
     * 
     */
    Synthesizer() = default;

    /**
     * @brief Destroy the Synthesizer object
     * 
     */
    ~Synthesizer() = default;
    
    /**
     * @brief Export a completed @ref Grid to a file of the specified format.
     * @param grid A completed grid of tiles.
     * @param exportPath The path for the exported image.
     * @param type The format for the image.
     */
    void exportGridToFile(const Grid<Solver::TileKey>& grid, std::string exportPath, FileType type);

    /**
     * @brief Export a completed @ref Grid to a @ref BMPImage.
     * 
     * @param grid A completed grid of tiles
     * @return std::shared_ptr<BMPImage> Caller gets the ownership of a smart pointer to the result image.
     */
    std::shared_ptr<BMPImage> exportGridToImage(const Grid<Solver::TileKey>& grid);
     
    /**
     * @brief Initialize a real time image for step by step images.
     * If there is an existing real time image, this function would clear the existing one. 
     * 
     * @param n The dimension of the image.
     */
    void initRealTimeImage(unsigned int n);

    /**
     * @brief Modify the real time image with one step of collapse in grid.
     * 
     * @param pos The logical position of the target position in grid.
     * @param tile The target tile to be filled into the position.
     */
    void modifyRealTimeImage(Position pos, const Tile& tile);

    /**
     * @brief Get the Real Time Image object
     * 
     * @return std::shared_ptr<BMPImage> The caller gains ownership of the real time image.
     */
    std::shared_ptr<BMPImage> getRealTimeImage() const;

    /**
     * @brief Clear the current real time image.
     * 
     */
    void clearRealTimeImage();
    
    /**
     * @brief Export the real time image to file in the specified format.
     * 
     * @param exportPath The target path for the exported image.
     * @param type The format of image.
     */
    void exportRealTimeImageToFile(std::string exportPath, FileType type);


private:

    /* IMAGE STATE */
    std::shared_ptr<BMPImage> realTimeImage;

    /* HELPER */
    void copyTileToGrid(Position pos, const Tile& tile, BMPImage* gridImage);

};
