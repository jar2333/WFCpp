#pragma once

#include <Extractor.h>
#include <Solver.h>
#include <Synthesizer.h>
#include <filesystem>
#include <cassert>
#include <iostream>

namespace fs = std::filesystem;

#define PRINTLOG

#ifdef PRINTLOG
#define LOG(str) do { std::cout << str << std::endl; } while( false )
#else
#define LOG(str) do { } while ( false )
#endif

const std::string assetDir = std::string(std::filesystem::current_path()) + "/test/assets";

std::shared_ptr<BMPImage> generateBMPByPixel(unsigned int size, Pixel pixel);

std::shared_ptr<Grid<Solver::TileKey>> generateCompleteGrid();

class SynthesizerTester
{
    public:
        SynthesizerTester();
        ~SynthesizerTester() = default;

        void runAll();

        void testExportGridToFile();
        void testExportGridToImage();
        void testRealTimeImage();

    private:
        Synthesizer syn;
        std::shared_ptr<Grid<Solver::TileKey>> grid;
        BMPImage sampleImage;
        BMPImage sampleImageRt;
};

class BMPImageTester
{
    public:
        BMPImageTester() = default;
        ~BMPImageTester() = default;

        void runAll();

        void testSetSize();
        void testSetPixel();
        void testCmpBMPImage();

        void testConstructByFile();
        void testExportToFile();

};