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

	e.setDumpDirectoryRelative(assetsDump);
	e.setAssetDirectoryRelative(assetsLocation);
	e.printDirectories();

	//extract here
	e.extractPNG(width, height, assetName, pixels);
	e.extractTileset(width, height, horizontal, vertical, pixels, tiles);
	e.setConstraints(tiles);	
	e.encodeTilesetPNG(tiles,assetName);
	
	for(auto t = tiles.begin(); t != tiles.end(); ++t){
		e.printConstraints(*t);
	}
	
	std::cout << width << "x" << height << std::endl; 
	
}

void ExtractorTester::runAll() {
    testExtractor();
}
