#include "Test.h"

void BMPImageTester::testSetSize() {

    LOG("BMPImageTester: testSetSize");

    auto image = BMPImage(1, 1);

    image.setSize(5, 5);

    auto width = image.getWidth();
    auto height = image.getHeight();

    assert(width == 5);
    assert(height == 5);

}

void BMPImageTester::runAll() {
    testConstructByFile();
    testExportToFile();

    testSetSize();
    testSetPixel();
    testCmpBMPImage();
    LOG("");
}

void BMPImageTester::testSetPixel() {
    LOG("BMPImageTester: testSetPixel");

    auto image = BMPImage(10, 10);

    image.setPixel({0, 0}, {0, 255, 255, 255, 255});
    image.setPixel({5, 5}, {0, 100, 255, 100, 255});

    auto pixel = image.getPixel({0, 0});
    assert(pixel == Pixel ({0, 255, 255, 255, 255}));

    pixel = image.getPixel({5, 5});
    assert(pixel == Pixel ({0, 100, 255, 100, 255}));

}

void BMPImageTester::testCmpBMPImage() {
    LOG("BMPImageTester: testCmpBMPImage");

    auto image1 = BMPImage(assetDir + "/Grass.png");
    auto image2 = BMPImage(assetDir + "/Grass.png");

    assert(image1 == image2);

    image1 = BMPImage(assetDir + "/synthesizer_test_sample.bmp");
    image2 = BMPImage(assetDir + "/Grass.png");

    assert(image1 != image2);

    image1 = BMPImage(assetDir + "/synthesizer_test_sample.bmp");
    image2 = BMPImage(assetDir + "/synthesizer_test_sample_rt.bmp");

    assert(image1 != image2);

}

void BMPImageTester::testConstructByFile() {
    LOG("BMPImageTester: testConstructByFile");

    auto imagePNG = BMPImage(assetDir + "/Grass.png");
    LOG("   Constructed from PNG");

    auto imageBMP = BMPImage(assetDir + "/Grass.bmp");
    LOG("   Constructed from BMP");

    assert(imagePNG == imageBMP);
}

void BMPImageTester::testExportToFile() {
    LOG("BMPImageTester: testExportToFile");
    auto image = BMPImage(assetDir + "/Grass.png");
    image.exportToFile(assetDir + "/test_BMPImage_export.png", FileType::png);
    assert(fs::exists(assetDir + "/test_BMPImage_export.png"));
    image.exportToFile(assetDir + "/test_BMPImage_export.bmp", FileType::bmp);
    assert(fs::exists(assetDir + "/test_BMPImage_export.bmp"));

    LOG("   Images exported at: test_BMPImage_export");
}