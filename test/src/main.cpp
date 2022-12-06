#include "Test.h"

void testExtractor() {
	Extractor e;
	std::vector<Pixel> pixels;
	std::vector<TileData> tiles;
	unsigned int width, height;
	//std::string filename = "Edge_n.png";
	std::string dir = std::string(std::filesystem::current_path())+"/test/assets";

	std::cout << dir << "\n";

	std::string filename = dir+"/Grass.png";
	
	TileData tile1;

	e.extractPNG(&width, &height, &filename, &pixels);
	e.extractTileset(width, height, 5, 1, pixels, &tiles);
	
	int counter = 1;
	
	for(std::vector<TileData>::iterator it = tiles.begin(); it != tiles.end(); ++it){
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


template <typename T>
void print(T a, std::string container) {
    std::cout << container << ": ";
    for (auto k : a) {
        std::cout << k << ", ";
    }
    std::cout << std::endl;
}

void testSolver() {
	std::vector<std::string> tiles;

    tiles.push_back("grass");
    tiles.push_back("grass-sky");
    tiles.push_back("sky");
    tiles.push_back("bird");   

    std::cout << "Seed: ";
    int seed;
    std::cin >> seed;
    Solver solver = Solver(tiles, seed);

    solver.addAdjacencyConstraint(0, Direction::UP, {0, 1});
    solver.addAdjacencyConstraint(0, Direction::DOWN, {0});
    solver.addAdjacencyConstraint(0, Direction::LEFT, {0});
    solver.addAdjacencyConstraint(0, Direction::RIGHT, {0});

    solver.addAdjacencyConstraint(1, Direction::UP, {2});
    solver.addAdjacencyConstraint(1, Direction::DOWN, {0});
    solver.addAdjacencyConstraint(1, Direction::LEFT, {1});
    solver.addAdjacencyConstraint(1, Direction::RIGHT, {1});

    solver.addAdjacencyConstraint(2, Direction::UP, {2,3});
    solver.addAdjacencyConstraint(2, Direction::DOWN, {1,2,3});
    solver.addAdjacencyConstraint(2, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraint(2, Direction::RIGHT, {2,3});

    solver.addAdjacencyConstraint(3, Direction::UP, {2,3});
    solver.addAdjacencyConstraint(3, Direction::DOWN, {1,2,3});
    solver.addAdjacencyConstraint(3, Direction::LEFT, {2,3});
    solver.addAdjacencyConstraint(3, Direction::RIGHT, {2,3});

    solver.setInitialConstraint({2,3}, {1});

    solver.registerOnCollapse([&tiles](const Solver::TileKey& k, Position p){
        auto [i, j] = p;
        std::cout << "Collapse! at Position: (" << i << ", " << j << "), tile: " << tiles[k] << std::endl;
    });

    solver.registerOnPropagate([](const std::vector<Solver::TileKey>& k, Position p){
        auto [i, j] = p;
        std::cout << "Propagate! at Position: (" << i << ", " << j << "), ";
        print(k, "tiles: ");
    });

    int gridSize = 7;

    auto grid = solver.solve(gridSize);

    for (int i = 0; i < gridSize; i++) {
      for (int j = 0; j < gridSize; j++) {
        std::cout << "Position: (" << i << ", " << j << "), tile: " << tiles[grid.getKey({i, j})] << std::endl;
      }
    }

}


int main() {
	// testExtractor();
	// testSolver();

    BMPImageTester imgTester;
    imgTester.runAll();

    SynthesizerTester synTester;
    synTester.runAll();

    return 0;
}
