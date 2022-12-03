#include "lodepng.h"
#include "EasyBMP.h"
#include "EasyBMP_BMP.h"

#include <Extractor.h>

#include <vector>
#include <string>
#include <iostream>

int Extractor::tileFormation(std::vector<Pixel>* pixels, TileData* tile, unsigned int width, unsigned int height){
	std::vector<Pixel> north;
	std::vector<Pixel> south;
	std::vector<Pixel> east;
	std::vector<Pixel> west;
	
	
	tile->pixels = *pixels;
	tile->width = width;
	tile->height = height;


	std::vector<Pixel>::iterator it = (*pixels).begin();

	for(unsigned int i = 0; i < width; i++){
		north.push_back(*it);
		it++;
	}	

	it = (*pixels).end();
	it = it - width;
	
	for(unsigned int i = 0; i < width; i++){
		south.push_back(*it);
		it++;
	}

	it = (*pixels).begin();

	for(unsigned int i = 0; i < height; i++){
		west.push_back(*it);
		it = it + width;
	}

	it = (*pixels).begin();
	it = it + width - 1;

	for(unsigned int i = 0; i < height; i++){
		east.push_back(*it);
		it = it + width;
	}

	tile->north = north;
	tile->south = south;
	tile->east = east;
	tile->west = west;

	return 1;
}

int Extractor::setConstraints(TileData tile, std::vector<TileData> tileList){
	
	return 1;
}

int Extractor::tileCompare(TileData tile1, TileData tile2){
	
	return 0;
}

int Extractor::sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length, Side side){
	
	return 1;
}

int Extractor::extractPNG(unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels) {
	std::vector<unsigned char> image;
	int counter = 1; 
	int colorCounter = 1;
	Pixel p;

	unsigned error = lodepng::decode(image, *width, *height, *filename);
	
	if(error){
		std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
		return 0;
	}

	for(std::vector<unsigned char>::iterator it = image.begin() ; it != image.end(); ++it){
		std::cout <<  counter << ": " << (int) *it << std::endl;
		counter++;
		switch(colorCounter){
			case 1:
				p.R = (int) *it;
				colorCounter++;
				break;
			case 2:
				p.G = (int) *it;
				colorCounter++;
				break;
			case 3:
				p.B = (int) *it;
				colorCounter++;
				break;
			case 4:
				p.A = (int) *it;
				colorCounter = 1;
				(*pixels).push_back(p);
				break;
		}

	}
	
	return 1;


}

int Extractor::extractBMP(unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels){
	BMP image;
	image.ReadFromFile((*filename).c_str()); 			

	std::cout << (*filename).c_str() << std::endl;
		
	*width = (unsigned int) image.TellWidth();
	*height = (unsigned int) image.TellHeight();

	Pixel p;

	for(int j = 0; j < *height; j++){
		
		for(int i = 0; i < *width; i++){
			
			p.R = image(i,j)->Red;
			p.G = image(i,j)->Green;
			p.B = image(i,j)->Blue;
			(*pixels).push_back(p);	
		}
	}
	
	
	return 1;
}


int Extractor::extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, std::vector<Pixel> pixels, std::vector<TileData>* tiles){
	Extractor e;
	unsigned int newWidth = width / horizontal; 
	unsigned int newHeight = height / vertical; 
	int widthCounter = 0;
	int heightCounter = 0;
	std::vector<Pixel> tilePixels;	

	for(int i = 0; i < vertical; i++){
		std::cout << "i: " << i << std::endl;
		for(int j = 0; j < horizontal; j++){
			std::cout << "j: " << j << std::endl;
			TileData t;

			for(std::vector<Pixel>::iterator it = (pixels.begin() + (i * width * newHeight) + (j * newWidth)) ; it != pixels.end(); ++it){

				if(widthCounter == newWidth){
					it = pixels.begin() + (i * width * newHeight) + (j * newWidth);
					heightCounter++;
					if(heightCounter == newHeight){
						heightCounter = 0;
						break;
					}
					it = it + (heightCounter * width);
					widthCounter = 0;	
				}

				std::cout << widthCounter << ":" << heightCounter << std::endl;
				tilePixels.push_back(*it);
				widthCounter++;
			}
			e.tileFormation(&tilePixels,&t, newWidth, newHeight);
			(*tiles).push_back(t);
			tilePixels.clear();
			widthCounter = 0;
		}
	}
	
		
	return 1;
}	

int Extractor::encodePNG(unsigned int width, unsigned int height, std::string filename, std::vector<Pixel> pixels) {
	std::vector<unsigned char> image;
	unsigned char r,g,b,a;

	for(std::vector<Pixel>::iterator it = pixels.begin(); it != pixels.end(); ++it){
		r =  (unsigned char) ((*it).R);
		g =  (unsigned char) ((*it).G);
		b =  (unsigned char) ((*it).B);
		a =  (unsigned char) ((*it).A);
		image.push_back(r);
		image.push_back(g);
		image.push_back(b);
		image.push_back(a);
	}

	lodepng::encode(filename, image, width, height);
	
	
	return 1; 
}
