#pragma once

#include <Pixel.h>

#include <vector>
#include <string>

enum Side { north, south, east, west };

class TileData {
	public: 
		unsigned int width, height;
		std::vector<Pixel> pixels;
		
		std::vector<Pixel> north;
		std::vector<Pixel> south;
		std::vector<Pixel> east;
		std::vector<Pixel> west;
		
		std::vector<TileData> northConstraints;
		std::vector<TileData> southConstraints;
		std::vector<TileData> westConstraints;
		std::vector<TileData> eastConstraints;
};

class Extractor {
	public: 
		int extractPNG(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);	
		int extractBMP(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);

		int extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, const std::vector<Pixel>& pixels, std::vector<TileData>& tiles);

 		static int encodePNG(unsigned int width, unsigned int height, const std::string& filename, const std::vector<Pixel>& pixels);

	private:

		int tileFormation(const std::vector<Pixel>& pixels, TileData& tile, unsigned int width, unsigned int height);

		int setConstraints(TileData tile, std::vector<TileData> tileList);
		int tileCompare(TileData tile1, TileData tile2);
		int sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length, Side side);

		int stuff;
};
