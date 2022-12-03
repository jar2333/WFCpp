#pragma once

#include <vector>
#include <string>

enum Side { north, south, east, west };

class Pixel {
	public:
		int count;
		int R;
		int G;
		int B;
		int A;
};

class Tile {
	public: 
		unsigned int width, height;
		std::vector<Pixel> pixels;
		
		std::vector<Pixel> north;
		std::vector<Pixel> south;
		std::vector<Pixel> east;
		std::vector<Pixel> west;
		
		std::vector<Tile> northConstraints;
		std::vector<Tile> southConstraints;
		std::vector<Tile> westConstraints;
		std::vector<Tile> eastConstraints;
};

class Extractor {
	public: 
		int extractPNG(unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels);	
		int extractBMP(unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels);
		int extractTileset(unsigned int width, unsigned int height, unsigned int Horizontal, unsigned int Vertical, std::vector<Pixel> pixels, std::vector<Tile>* tiles);
		int tileFormation(std::vector<Pixel>* pixels, Tile* tile, unsigned int width, unsigned int height);
		int setConstraints(Tile tile, std::vector<Tile> tileList);
		int tileCompare(Tile tile1, Tile tile2);
		int sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length, Side side);

        static int encodePNG(unsigned int width, unsigned int height, std::string filename, std::vector<Pixel> pixels);
	private: 
		int stuff;
};