#pragma once

#include <Pixel.h>

#include <vector>
#include <string>
#include <map>

enum Side { north, south, east, west };

class TileData {
	public: 
		int id;
		unsigned int width, height;
		std::vector<Pixel> pixels;
		
		std::vector<Pixel> north;
		std::vector<Pixel> south;
		std::vector<Pixel> east;
		std::vector<Pixel> west;
		
		std::map<int, std::vector<int>> northConstraints;
		std::map<int, std::vector<int>> southConstraints;
		std::map<int, std::vector<int>> westConstraints;
		std::map<int, std::vector<int>> eastConstraints;
};

class Extractor {
	public:
	        int idCount;
		double comparisonMetric;

		int extractPNG(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);	
		int extractBMP(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels);

		int extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, const std::vector<Pixel>& pixels, std::vector<TileData>& tiles);

 		static int encodePNG(unsigned int width, unsigned int height, const std::string& filename, const std::vector<Pixel>& pixels);
		
		int setConstraints(std::vector<TileData>& tileList);

		Extractor(){
			idCount = 1;
			comparisonMetric = .1;
		}

	private:

		int tileFormation(const std::vector<Pixel>& pixels, TileData& tile, unsigned int width, unsigned int height, int id);

		int tileCompare(TileData& tile1, TileData& tile2);
		bool sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length);

		int stuff;
};
