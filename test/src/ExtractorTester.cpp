#include "Test.h"

void ExtractorTester::testExtractor() {
	Extractor e;
	std::vector<Pixel> pixels;
	std::vector<TileData> tiles;
	unsigned int width, height;
	int horizontal, vertical;

	std::string assetsLocation = "/../../test/assets";
	std::string assetsDump = "/../../test/assets/tiles";
	
	//std::string assetName = "/Grass";
	std::string assetName;

	std::cout << "Enter the name of the Tile/Tileset you wish to extract: ";
	std::cin >> assetName;
	std::cout << std::endl;
	assetName = "/" + assetName;


	std::cout << "Enter the number of tiles horizontal on the Tileset you've entered (1, for a single tile): ";
	std::cin >> horizontal;
	std::cout << std::endl; 

	
	std::cout << "Enter the number of tiles vertical on the Tileset you've entered (1, for a single tile): ";
	std::cin >> vertical;
	std::cout << std::endl;

	
	std::string dirL = std::string(std::filesystem::current_path())+ assetsLocation;
	std::string dirD = std::string(std::filesystem::current_path())+ assetsDump;

	std::cout << dirL << "\n";
	std::cout << dirD << "\n";

	std::string filename = dirL + assetName + ".png";
	
	std::filesystem::create_directories(dirD + assetName);
	std::filesystem::permissions(dirD + assetName, std::filesystem::perms::others_all | std::filesystem::perms::group_all | std::filesystem::perms::owner_all); 
	TileData tile1;


	//extract here
	//e.comparisonMetric = 0;
	e.extractPNG(width, height, filename, pixels);
	e.extractTileset(width, height, horizontal, vertical, pixels, tiles);
	e.setConstraints(tiles);	

	int counter = 1;
	int i = 0;

	for(auto it = tiles.begin(); it != tiles.end(); ++it){
		std::cout << counter << ": " << it->width << ", " << it->height << std::endl;
		
		int id = it->id;
		std::set<int>::iterator j;
		i = 0;	

		while(i < 4){

			switch(i){
				
				case 0:
					j = it->northConstraints[id].begin();
					std::cout << it->id << " north: ";
					while(j != it->northConstraints[id].end()){
						std::cout << *j << ", ";
						j++;
					}
					std::cout << std::endl; 
					break;
				case 1:
					j = it->southConstraints[id].begin();
					std::cout << it->id << " south: ";
					while(j != it->southConstraints[id].end()){
						std::cout << *j << ", ";
						j++;
					}
					std::cout << std::endl; 
					break;
				case 2:
					j = it->eastConstraints[id].begin();
					std::cout << it->id << " east: ";
					while(j != it->eastConstraints[id].end()){
						std::cout << *j << ", ";
						j++;
					}
					std::cout << std::endl; 
					break;
				case 3: 
					j = it->westConstraints[id].begin(); 
					std::cout << it->id << " west: ";
					while(j != it->westConstraints[id].end()){
						std::cout << *j << ", ";
						j++;
					}
					std::cout << std::endl << std::endl; 
					break; 
			}
			i++;
			

		}

        	std::string name = dirD + assetName + "/" + std::to_string(counter) + ".png";
		
		//encode here
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

void ExtractorTester::runAll() {
    testExtractor();
}
