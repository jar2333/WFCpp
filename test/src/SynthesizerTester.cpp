#include "Test.h"

std::shared_ptr<BMPImage> generateBMPByPixel(unsigned int size, Pixel pixel)
{
    auto img = std::make_shared<BMPImage> (size, size);
    for (unsigned int i = 0; i < size; i++)
        for (unsigned int j = 0; j < size; j++) {
            Position pos = {i, j};
            img->setPixel(pos, pixel);
        }
    return img;
}

std::shared_ptr<Grid<Solver::TileKey>> generateCompleteGrid()
{
    auto img1 = generateBMPByPixel(3, {0, 255, 255, 255, 255}); // white
    auto img2 = generateBMPByPixel(3, {0, 0, 0, 0, 255});       // black

    auto tile1 = std::make_shared<Tile> (img1);
    auto tile2 = std::make_shared<Tile> (img2);


    std::map<Solver::TileKey, std::shared_ptr<Tile>> tileMap;

    tileMap[Solver::TileKey(1)] = tile1;
    tileMap[Solver::TileKey(2)] = tile2;


    auto grid = std::make_shared<Grid<Solver::TileKey>> (3, tileMap);


    for (const auto pos : grid->enumeratePosition()) {
        grid->setTile(pos, Solver::TileKey(pos.x % 2 + 1));
    }

    return grid;
}

SynthesizerTester::SynthesizerTester()
{
    LOG("SynthesizerTester: initializing...");
    syn = Synthesizer();
    grid = generateCompleteGrid();
    LOG("   Generated grid");
    sampleImage = BMPImage(assetDir + "/synthesizer_test_sample.bmp");
    LOG("   Loaded image from " << assetDir << "/synthesizer_test_sample.bmp");
    sampleImageRt = BMPImage(assetDir + "/synthesizer_test_sample_rt.bmp");
    LOG("   Loaded image from " << assetDir << "/synthesizer_test_sample_rt.bmp");

}

void SynthesizerTester::runAll()
{
    testExportGridToFile();
    testExportGridToImage();
    testRealTimeImage();
    LOG("");
}

void SynthesizerTester::testExportGridToFile()
{
    LOG("SynthesizerTester: testExportGridToFile");
    std::string exportPath = assetDir + "/test_synthesizer";
    syn.exportGridToFile(*grid, exportPath + ".png", FileType::png);
    assert(fs::exists(exportPath + ".png"));
    syn.exportGridToFile(*grid, exportPath + ".bmp", FileType::bmp);
    assert(fs::exists(exportPath + ".bmp"));

    LOG("   Images exported at: " << exportPath);

    auto img = BMPImage(exportPath + ".bmp");
    assert(img == sampleImage);
}

void SynthesizerTester::testExportGridToImage()
{
    LOG("SynthesizerTester: testExportGridToImage");
    auto resImg = syn.exportGridToImage(*grid);
    assert(*resImg == sampleImage);
}

void SynthesizerTester::testRealTimeImage()
{
    LOG("SynthesizerTester: testRealTimeImage");

    LOG("   Init image");
    syn.initRealTimeImage(9);
    auto img = syn.getRealTimeImage();
    assert(img->getHeight() == 9);
    assert(img->getWidth() == 9);

    LOG("   Modify image");
    auto pos = grid->translatePixelPosition({1, 1});
    syn.modifyRealTimeImage(pos, *(grid->getTile({1, 1})));
    assert((*img) == sampleImageRt);

    LOG("   Export image");
    auto path = assetDir + "/test_synthesizer_rt.bmp";
    syn.exportRealTimeImageToFile(path, FileType::bmp);
    assert(fs::exists(path));
    auto exportImg = BMPImage(path);
    assert(exportImg == sampleImageRt);

    LOG("   Clear image");
    syn.clearRealTimeImage();
    assert(syn.getRealTimeImage() == nullptr);
}