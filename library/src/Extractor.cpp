#include <Extractor.h>
#include <lodepng.h>
#include <EasyBMP.h>

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <filesystem>

int Extractor::tileFormation(const std::vector<Pixel>& pixels, TileData& tile, unsigned int width, unsigned int height, int id){
	std::vector<Pixel> north;
	std::vector<Pixel> south;
	std::vector<Pixel> east;
	std::vector<Pixel> west;
	
	tile.pixels = pixels;
	tile.width = width;
	tile.height = height;
	tile.id = id;

	tile.northConstraints.insert(std::pair<int,std::set<int>> (id, std::set<int>())); 
	tile.southConstraints.insert(std::pair<int,std::set<int>> (id, std::set<int>())); 
	tile.eastConstraints.insert(std::pair<int,std::set<int>> (id, std::set<int>())); 
	tile.westConstraints.insert(std::pair<int,std::set<int>> (id, std::set<int>())); 

	// std::vector<Pixel>::iterator it = pixels.begin();
	auto it = pixels.begin();

	for(unsigned int i = 0; i < width; i++){
		north.push_back(*it);
		it++;
	}	

	it = pixels.end();
	it = it - width;
	
	for(unsigned int i = 0; i < width; i++){
		south.push_back(*it);
		it++;
	}

	it = pixels.begin();

	for(unsigned int i = 0; i < height; i++){
		west.push_back(*it);
		it = it + width;
	}

	it = pixels.begin();
	it = it + width - 1;

	for(unsigned int i = 0; i < height; i++){
		east.push_back(*it);
		it = it + width;
	}

	//use std::move? :]
	tile.north = north;
	tile.south = south;
	tile.east = east;
	tile.west = west;

	return 1;
}

int Extractor::setConstraints(std::vector<TileData>& tileList){
	std::vector<TileData>::iterator it1 = tileList.begin();

	
	for(std::vector<TileData>::iterator it1 = tileList.begin(); it1 != tileList.end(); ++it1){
		for(std::vector<TileData>::iterator it2 = tileList.begin(); it2 != tileList.end(); ++it2){
			if(it1->id != it2->id){
				Extractor::tileCompare(*it1, *it2);
			}
		}
	}
	
	
	return 1;
}

void Extractor::setComparisonMetric(double m){
	comparisonMetric = m;
}

void Extractor::setAssetDirectoryAbsolute(std::string dir){
	aDir = dir;
}

void Extractor::setAssetDirectoryRelative(std::string dir){
	aDir = std::string(std::filesystem::current_path()) + dir;
}

void Extractor::setDumpDirectoryRelative(std::string dir){
	dDir = std::string(std::filesystem::current_path()) + dir;
}

void Extractor::setDumpDirectoryAbsolute(std::string dir){
	dDir = dir;
}

void Extractor::printDirectories(){
	std::cout << "asset directory: " << aDir << std::endl;
	std::cout << "dump directory: " << dDir << std::endl;
	
}

void Extractor::printConstraintsV(std::vector<TileData> tiles){
	for(auto i = tiles.begin(); i != tiles.end(); ++i){
		Extractor::printConstraints(*i);

	}

}

void Extractor::printConstraints(TileData tile){
	int id = tile.id;
	std::set<int>::iterator j;
	int i = 0;	

	while(i < 4){
		switch(i){
			
			case 0:
				j = tile.northConstraints[id].begin();
				std::cout << tile.id << " north: ";
				while(j != tile.northConstraints[id].end()){
					std::cout << *j << ", ";
					j++;
				}
				std::cout << std::endl; 
				break;
			case 1:
				j = tile.southConstraints[id].begin();
				std::cout << tile.id << " south: ";
				while(j != tile.southConstraints[id].end()){
					std::cout << *j << ", ";
					j++;
				}
				std::cout << std::endl; 
				break;
			case 2:
				j = tile.eastConstraints[id].begin();
				std::cout << tile.id << " east: ";
				while(j != tile.eastConstraints[id].end()){
					std::cout << *j << ", ";
					j++;
				}
				std::cout << std::endl; 
				break;
			case 3: 
				j = tile.westConstraints[id].begin(); 
				std::cout << tile.id << " west: ";
				while(j != tile.westConstraints[id].end()){
					std::cout << *j << ", ";
					j++;
				}
				std::cout << std::endl << std::endl; 
				break; 
		}
		i++;
		
	}

}

int Extractor::tileCompare(TileData& tile1, TileData& tile2){
	int length = tile1.width;
	int length2 = tile2.width;

	Side sides[4] = {north, south, east, west};

	for(int i = 0; i < 4; i++){
		switch(sides[i]){
			case north:
				if(Extractor::sideCompare(tile1.north, tile2.south, length)){
					tile1.northConstraints[tile1.id].insert(tile2.id);	
					tile2.southConstraints[tile2.id].insert(tile1.id);	
				}
				break;
			case south:
				if(Extractor::sideCompare(tile1.south, tile2.north, length)){
					tile1.southConstraints[tile1.id].insert(tile2.id);	
					tile2.northConstraints[tile2.id].insert(tile1.id);	
				}
				break;
			case east: 
				if(Extractor::sideCompare(tile1.east, tile2.west, length)){
					tile1.eastConstraints[tile1.id].insert(tile2.id);	
					tile2.westConstraints[tile2.id].insert(tile1.id);	
				}
				break;
			case west:
				if(Extractor::sideCompare(tile1.west, tile2.east, length)){
					tile1.westConstraints[tile1.id].insert(tile2.id);	
					tile2.eastConstraints[tile2.id].insert(tile1.id);	
				}
				break;
		}
	}	

	return 1;
}

bool Extractor::sideCompare(std::vector<Pixel> side1, std::vector<Pixel> side2, unsigned int length){
	int r,g,b,r2,g2,b2;
	double rDif, gDif, bDif, avgPixelDif;
	double avgTotalDif = 0;

	std::vector<Pixel>::iterator it1 = side1.begin();
	std::vector<Pixel>::iterator it2 = side2.begin();
	
	for(int i = 0; i < length; i++){
		r = (int) it1->Red;
		g = (int) it1->Green;
		b = (int) it1->Blue;
		r2 = (int) it2->Red;
		g2 = (int) it2->Green;
		b2 = (int) it2->Blue;
		rDif = abs(r - r2)/255.0;
		gDif = abs(g - g2)/255.0;
		bDif = abs(b - b2)/255.0;
		avgPixelDif = (rDif + gDif + bDif)/3; 
		avgTotalDif += avgPixelDif;
	
		//std::cout << i << std::endl;	
		//std::cout << (int) it1->Red << " " << (int) it2->Red << std::endl;
		//std::cout << (int) it1->Green << " " << (int) it2->Green << std::endl;
		//std::cout << (int) it1->Blue << " " << (int) it2->Blue << std::endl;

		++it1;
		++it2;
	}
	
	avgTotalDif = avgTotalDif / length;
	

	
	double comparison = 1 - avgTotalDif;

	//std::cout << rDif << " ";
	//std::cout << gDif << " ";
	//std::cout << bDif << " ";
	
	//std::cout << avgTotalDif << " " << comparison <<  ":sideCompare\n";


	if(comparison >= comparisonMetric){
		//std::cout << "true" << std::endl;
		return true;
	}
	
	//std::cout << "false" << std::endl;

	return false;
}

void Extractor::encodeTilesetPNG(std::vector<TileData>& tiles, std::string assetName){
	int counter = 1;
	int i = 0;
	std::filesystem::create_directories(dDir + assetName);
	std::filesystem::permissions(dDir + assetName, std::filesystem::perms::others_all | std::filesystem::perms::group_all | std::filesystem::perms::owner_all); 

	for(auto it = tiles.begin(); it != tiles.end(); ++it){
		//std::cout << counter << " width: " << it->width << std::endl;
		//std::cout << counter << " height: " << it->height << std::endl;
		
		//e.printConstraints(*it);	

        	std::string name = dDir + assetName + "/" + std::to_string(counter) + ".png";
		//std::cout << name << std::endl;	
		//encode here
        	Extractor::encodePNG(it->width, it->height, name, it->pixels);
	
		counter++;
    	}	

}	

void Extractor::extractPNG(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels) {
	std::vector<unsigned char> image;
	int counter = 1; 
	int colorCounter = 1;
	Pixel p;
	
	std::string dir = aDir + filename + ".png";	


	unsigned error = lodepng::decode(image, width, height, dir);
	
	if(error){
		std::cout << "decoder error" << error << ": " << lodepng_error_text(error) << std::endl;
	}

	for(std::vector<unsigned char>::iterator it = image.begin() ; it != image.end(); ++it){
		// std::cout <<  counter << ": " << (int) *it << std::endl;
		counter++;
		switch(colorCounter){
			case 1:
				p.Red = *it;
				colorCounter++;
				break;
			case 2:
				p.Green = *it;
				colorCounter++;
				break;
			case 3:
				p.Blue = *it;
				colorCounter++;
				break;
			case 4:
				p.Alpha = *it;
				colorCounter = 1;
				pixels.push_back(p);
				break;
		}

	}


}

void Extractor::extractBMP(unsigned int& width, unsigned int& height, const std::string& filename, std::vector<Pixel>& pixels){
	BMP image;
	image.ReadFromFile(filename.c_str()); 			

	// std::cout << (*filename).c_str() << std::endl;
		
	width = (unsigned int) image.TellWidth();
	height = (unsigned int) image.TellHeight();

	Pixel p;

	for(unsigned int j = 0; j < height; j++) {
		for(unsigned int i = 0; i < width; i++) {
			p.Red = image(i,j)->Red;
			p.Green = image(i,j)->Green;
			p.Blue = image(i,j)->Blue;
			pixels.push_back(p);	
		}
	}
	
}


int Extractor::extractTileset(unsigned int width, unsigned int height, unsigned int horizontal, unsigned int vertical, const std::vector<Pixel>& pixels, std::vector<TileData>& tiles){
	Extractor e;

	unsigned int newWidth = width / horizontal; 
	unsigned int newHeight = height / vertical; 

	unsigned int widthCounter = 0;
	unsigned int heightCounter = 0;

	std::vector<Pixel> tilePixels;	

	for(unsigned int i = 0; i < vertical; i++){
		// std::cout << "i: " << i << std::endl;
		for(unsigned int j = 0; j < horizontal; j++){
			// std::cout << "j: " << j << std::endl;
			TileData t;

			for(auto it = (pixels.begin() + (i * width * newHeight) + (j * newWidth)) ; it != pixels.end(); ++it){

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

				// std::cout << widthCounter << ":" << heightCounter << std::endl;
				tilePixels.push_back(*it);
				widthCounter++;
			}
			e.tileFormation(tilePixels, t, newWidth, newHeight, idCount);
			idCount++;
			tiles.push_back(t);
			tilePixels.clear();
			widthCounter = 0;
		}
	}
	
		
	return 1;
}	

void Extractor::encodePNG(unsigned int width, unsigned int height, const std::string& filename, const std::vector<Pixel>& pixels) {
	std::vector<unsigned char> image;
	unsigned char r,g,b,a;

	for(auto it = pixels.begin(); it != pixels.end(); ++it){
		r =  (unsigned char) (it->Red);
		g =  (unsigned char) (it->Green);
		b =  (unsigned char) (it->Blue);
		a =  (unsigned char) (it->Alpha);
		image.push_back(r);
		image.push_back(g);
		image.push_back(b);
		image.push_back(a);
	}

	lodepng::encode(filename, image, width, height);
}
