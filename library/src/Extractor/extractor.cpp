#include <iostream> 
#include "lodepng.h"

class Pixel {
	public:
		int count;
		int R;
		int G;
		int B;
		int A;
};

class Extractor {
	public: 
		int extractPNG(std::vector<unsigned char>* image, unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels);
	private: 
		int stuff;
};


int Extractor::extractPNG(std::vector<unsigned char>* image, unsigned int* width, unsigned int* height, std::string* filename, std::vector<Pixel>* pixels){
	int counter = 1; 
	int colorCounter = 1;
	Pixel p;

	unsigned error = lodepng::decode(*image, *width, *height, *filename);
	
	if(error){
		std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
		return 0;
	}

	for(std::vector<unsigned char>::iterator it = (*image).begin() ; it != (*image).end(); ++it){
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
	
	std::cout << '\n' << *width << '\n' << *height << '\n';

	return 1;


}

int main(int arc, char** argv){
	Extractor e;
	std::vector<unsigned char> image;
	std::vector<Pixel> pixels;
	unsigned int width, height;
	std::string filename = "Edge_n.png";

	e.extractPNG(&image, &width, &height, &filename, &pixels);
	
	std::cout << width << "x" << height << std::endl; 

	int counter = 1;

	for(std::vector<Pixel>::iterator it = pixels.begin() ; it != pixels.end(); ++it){
		std::cout << counter  << ": " << (*it).R << "," << (*it).G << "," << (*it).B << std::endl;
		counter++;
	}	
	return 0;

}


