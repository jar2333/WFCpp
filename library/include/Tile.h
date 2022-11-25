#include <string>
#include <Enums.h>

class Tile {

public:

    int getDimension();
    bool matchesColors(Tile other, Direction d);

    // TODO: loads image from filePath and returns image object
    // ImageObject getImageData(); 

private:

    int n;
    std::string filePath;

    // TODO: add other variables

};
