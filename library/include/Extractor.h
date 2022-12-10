#pragma once

#include <Pixel.h>

#include <vector>
#include <string>
#include <map>
#include <set>


enum Side { north, south, east, west };

/**
 * @class TileData
 * @brief Tile Data Class
 * @author Ricardo Figueroa
 *
 * Contains all the required TileData retrieved through the extraction. Most of the
 * names are self explanitory. Id, width, height, pixels... The different sides 
 * (north, south, east, west) however refer to the list of pixels that encompase those
 * sides for the tile. The side constraints however, contain a set of ids mapped to 
 * the id of the tile.  
 *
 *
 * */

class TileData {
	public: 
		int id;
		unsigned int width, height;
		std::vector<Pixel> pixels;
		
		std::vector<Pixel> north;
		std::vector<Pixel> south;
		std::vector<Pixel> east;
		std::vector<Pixel> west;
		
		std::map<int, std::set<int>> northConstraints;
		std::map<int, std::set<int>> southConstraints;
		std::map<int, std::set<int>> westConstraints;
		std::map<int, std::set<int>> eastConstraints;
};


/**
 * @class Extractor
 * @brief The Extractor Class
 * @author Ricardo Figueroa
 *
 * This class provides support for the Wave Function Collapse algorithm by
 * making available png and bitmap extraction and encoding for tiles and tilesets. 
 * Tilesets are usually formatted in a X by X image file, so the extractor takes 
 * said image file and extracts all necessary information, i.e, pixel data, width and 
 * height. 
 *
 * There existed many methods by which to expand the extractor class. As a result of 
 * time constraints png and bmp are the only filetypes available for extraction. But 
 * by introducing more libraries to the class it can be possible to expand to a larger
 * range of filetypes, that said, the most common ones have been chosen for the class.
 *
 * Using both lodePNG and EasyBMP, extraction and encoding was made much easier. 
 * Allowing for simple to use API that abstract these processes. 
 *
 * Extraction for both PNG and BMP consists of acquiring the RGBA values of each pixel.
 * Ranging from 0 to 255 for each. They are placed in a vector of Pixel type that is 
 * meant to be the generalized structure for all extractions (space for appending functionality)
 *
 * Encoding for both PNG and BMP consists of taking this generalized structure and
 * encoding through their respective support libraries. 
 * 
 * The vectors of pixels as described above are then processed by extractTileset, which
 * is the function that creates the required piece for both the Solver and Synthesizer
 * (a vector of TileData). Given that the pixels themselves aren't organized in Tile form.
 *
 * Once the TileData is extracted it can then be automatically be setConstraints based
 * on a comparison metric. This is highly basic at the moment, the metric being a int meant 
 * to represent a percentage from 0 to 1.0. The difference in tile sides is calculated
 * and compared to this metric to decide whether the tiles are accepted as constraints.
 * This can be expanded on by changing the metric to some AI driven metric. Knowing 
 * what differernce in pixels is acceptable is hard to measure through simple 
 * arithmatic so for now it is just an option availble to the user.
 * 
 * 
 * @see Pixel
 * 
 * */


class Extractor {
	public:

		/**
		 * Extracts the pixel data from a PNG file.
		 * @param width A reference to width that gets updated on lodePNG extraction
		 * @param height A reference to height that gets updated on lodePNG extraction
		 * @param filename A reference to filename that is used to retrieve the desired file 
		 * @param pixels The pixel data of a file
		 *
		 * @see Pixel
		 */ 

		void extractPNG(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);	
		
		/**
		 * Extracts the pixel data from a BMP file.
		 * @param width A reference to width that gets updated on easyBMP extraction
		 * @param height A reference to height that gets updated on easyBMP extraction
		 * @param filename A reference to filename that is used to retrieve the desired file 
		 * @param pixels The pixel data of a file
		 *
		 * @see Pixel
		 */ 

		void extractBMP(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);

		/**
		 * Extracts tiles from a vector of pixels. 
		 *
		 * @param width The width of the file that extracted the pixels referenced in
		 * @param height The height of the file that extracted the pixels referenced in
		 * @param horizontal The maximum number of tiles on the tileset horizontally
		 * @param vertical The maxumum number of tiles on the tilset vertically
		 * @param pixels A reference to the pixels that will be extracted
		 * @param tiles A reference to the tile vector that will be appended to
		 *
		 * */

		int extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, const std::vector<Pixel>& pixels, std::vector<TileData>& tiles);

		/**
		 * Econdes a vecotr of tiles using encodePNG
		 *
		 * @param tiles The vector of tiles being encoded
		 * @param assetName name of asset and folder
		 * */

		void encodeTilesetPNG(std::vector<TileData>& tiles, std::string assetName);
		
		
		/**
		 * Encodes a vector of pixels into a PNG file at the filename provided.
		 * 
		 * @param width The width of the file being created
		 * @param height The height of the file being created
		 * @param filename The filename of the file being created
		 * @param pixels The pixels used to created the file
		 * 
		 * */

 		static void encodePNG(unsigned int width, unsigned int height, const std::string& filename, const std::vector<Pixel>& pixels);
		
		/**
		 * Set the constraints for each tile on a tileList based on the tiles
		 * from that tileList.
		 *
		 * @param tileList A vector of tiles to apply constraints to
		 * */

		int setConstraints(std::vector<TileData>& tileList);
		
		/**
		 * Setter function for comparisonMetric
		 * 
		 * @param m Input for comparisonMetric
		 * */ 

		void setComparisonMetric(double m);
	
		/**
		 *
		 * Directory setter for dumping extractions relative to current directory
		 *
		 *@param dir Directory
		 * */ 

		void setDumpDirectoryRelative(std::string dir);

		/**
		 *
		 * Directory setter for dumping assets
		 *
		 *@param dir Directory
		 * */ 
		
		void setDumpDirectoryAbsolute(std::string dir);
		
		/**
		 *
		 * Directory setter for acquiring assets relative to current directory
		 *
		 *@param dir Directory
		 * */ 

		void setAssetDirectoryRelative(std::string dir);

		/**
		 *
		 * Directory setter for acquiring assets
		 *
		 *@param dir Directory
		 * */ 

		void setAssetDirectoryAbsolute(std::string dir);	

		/**
		 * Print function for the two directories
		 * */

		void printDirectories();
		
		
		/**
		 * Print function for constraints of a vector of tiles
		 * 
		 * @param tile TileVector for printing
		 *  */

		void printConstraintsV(std::vector<TileData> tiles);
	
		/**
		 * Print function for constraints of a tile
		 * 
		 * @param tile Tile for printing
		 *  */

		void printConstraints(TileData tile);

		/**
		 * Default constructor for the Extractor.
		 * */

		Extractor(){
			idCount = 1;
			comparisonMetric = .8;
		}

		/**
		 * Constructor for the Extractor, allows for metric initialization.
		 *
		 * @param metric The metric the user is allowed to implement. Max at 
		 * 1, min at 0
		 * */

		Extractor(double metric){
			idCount = 1;
			if(metric > 1){
				metric = 1;
			}
			if(metric < 0){
				metric = 0;
			}

			comparisonMetric = metric;
		}

	private:

	        int idCount;
		double comparisonMetric;
		std::string aDir;
		std::string dDir;


		/**
		 * A function for abstraction of tile extraction. Given an empty tile 
		 * it gets filled with the appropriate information (constraints not included).
		 * @param pixels A reference to the pixels approrpiate for the tile being created
		 * @param tile A reference to the empty tile being filled
		 * @param width The width of the tile being created
		 * @param height The height of the tile being created
		 * @param id The id of the tile being created
		 * 
		 * */

		int tileFormation(const std::vector<Pixel>& pixels, TileData& tile, unsigned int width, unsigned int height, int id);

		/**
		 * A function for the abstraction of setConstraints. Compares the sides
		 * of two tiles. 
		 *
		 * @param tile1 A reference to the first tile being compared
		 * @param tile2 A reference to the second tile being compared
		 * */

		int tileCompare(TileData& tile1, TileData& tile2);
		
		/**
		 * A function for the abstraction of tileCompare. Compares two sides.
		 *
		 * @param side1 A vector of pixels for the first tile being compared 
		 * @param side2 A vector of pixels for the second tile being compared 
		 * @param length An integer representing the length of both tiles involved
		 * */

		bool sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length);

}
;
