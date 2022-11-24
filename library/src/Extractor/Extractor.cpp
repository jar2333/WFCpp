#include <iostream> 
#include "lodepng.h"

int main(int arc, char** argv){
	std::vector<unsigned char> image; //the raw pixels;
	unsigned int width, height;
	std::string filename = "Edge_n.png";
	int counter = 1;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);
	
	if(error){
		std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
	}

	for(std::vector<unsigned char>::iterator it = image.begin() ; it != image.end(); ++it){
		std::cout <<  counter << ": " << (int) *it << std::endl;
		counter++;
	}
	
	std::cout << '\n';

	

	
	
	return 0;

}
