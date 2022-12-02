#include <iostream> 
#include "lodepng.h"
#include "EasyBMP.h"
#include "EasyBMP_BMP.h"

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
		int encodePNG(unsigned int width, unsigned int height, std::string filename, std::vector<Pixel> pixels);	
		int tileFormation(std::vector<Pixel>* pixels, Tile* tile, unsigned int width, unsigned int height);
		int setConstraints(Tile tile, std::vector<Tile> tileList);
		int tileCompare(Tile tile1, Tile tile2);
		int sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length, Side side);
	private: 
		int stuff;
};

int Extractor::tileFormation(std::vector<Pixel>* pixels, Tile* tile, unsigned int width, unsigned int height){
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

int Extractor::setConstraints(Tile tile, std::vector<Tile> tileList){
	
	return 1;
}

int Extractor::tileCompare(Tile tile1, Tile tile2){
	
	return 0;
}

int Extractor::sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length, Side side){
	
	return 1;
}

int Extractor::extractPNG(unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels){
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
		//std::cout <<  counter << ": " << (int) *it << std::endl;
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

int encodePNG(unsigned int width, unsigned int height, std::string filename, std::vector<Pixel> pixels){
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


int Extractor::extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, std::vector<Pixel> pixels, std::vector<Tile>* tiles){
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
			Tile t;

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

int main(int arc, char** argv){
	Extractor e;
	std::vector<Pixel> pixels;
	std::vector<Tile> tiles;
	unsigned int width, height;
	//std::string filename = "Edge_n.png";
	std::string filename = "Grass.png";
	
	Tile tile1;


	e.extractPNG(&width, &height, &filename, &pixels);
	e.extractTileset(width, height, 5, 1, pixels, &tiles);
	
	int counter = 1;
	
	for(std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it){
		std::cout << counter << ": " << (*it).width << ", " << (*it).height << std::endl;
		
		switch(counter){
			case 1:
				encodePNG((*it).width, (*it).height, "New1.png", (*it).pixels);
				break;
			case 2:
				encodePNG((*it).width, (*it).height, "New2.png", (*it).pixels);
				break;
			case 3:
				encodePNG((*it).width, (*it).height, "New3.png", (*it).pixels);
				break;
			case 4:
				encodePNG((*it).width, (*it).height, "New4.png", (*it).pixels);
				break;
			case 5:
				encodePNG((*it).width, (*it).height, "New5.png", (*it).pixels);
				break;


		}
		counter++;
	}

	

		//e.extractBMP(&width2, &height2, &filename2, &pixels2);
		


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

	return 0;
}


