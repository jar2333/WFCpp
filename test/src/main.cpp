#include <Extractor.h>

#include <iostream>
#include <string>
#include <vector>

#include <filesystem>


void testExtractor() {
	Extractor e;
	std::vector<Pixel> pixels;
	std::vector<Tile> tiles;
	unsigned int width, height;
	//std::string filename = "Edge_n.png";
	std::string dir = std::string(std::filesystem::current_path())+"/test/assets";

	std::cout << dir << "\n";

	std::string filename = dir+"/Grass.png";
	
	Tile tile1;

	e.extractPNG(&width, &height, &filename, &pixels);
	e.extractTileset(width, height, 5, 1, pixels, &tiles);
	
	int counter = 1;
	
	for(std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it){
		std::cout << counter << ": " << it->width << ", " << it->height << std::endl;
		
        std::string name = dir + "/tiles/New" + std::to_string(counter) + ".png";

        Extractor::encodePNG(it->width, it->height, name, it->pixels);
	
		//e.extractBMP(&width2, &height2, &filename2, &pixels2);
		counter++;
    }
		


	//for(std::vector<Pixel>::iterator it = pixels.begin() ; it != pixels.end(); ++it){
	//	std::cout << counter << ": " << (*it).R << "," << (*it).G << "," << (*it).B << std::endl;
	//	counter++;
	//}	
	
	std::cout << width << "x" << height << std::endl; 
	
	//e.tileFormation(&pixels, &tile1, width, height);

	/*
	counter = 1;

	for(std::vector<Pixel>::iterator it = pixels2.begin() ; it != pixels2.end(); ++it){
		std::cout << counter  << ": " << (*it).R << "," << (*it).G << "," << (*it).B << std::endl;
		counter++;
	}
	
	std::cout << width2 << "x" << height2 << std::endl; 
	*/
}

int main() {
	testExtractor();
}
