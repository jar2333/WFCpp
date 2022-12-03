#include <vector>
#include <iostream>
#include <EasyBMP.h>
#include <lodepng.h>
#include <BMPImage.h>
#include <others.h>

#define LOG false

constexpr unsigned int defaultWidth = 5;
constexpr unsigned int defaultHeight = 5;

BMPImage::BMPImage()
{
    BMPImage(defaultWidth, defaultHeight);
}

BMPImage::BMPImage(unsigned int initWidth, unsigned int initHeight)
{
    setSize(initWidth, initHeight);

}

BMPImage::BMPImage(std::string filename)
{
    BMP image;
	image.ReadFromFile(filename.c_str()); 			

    if (LOG)
	    std::cout << filename << std::endl;
		
	width = (unsigned int) image.TellWidth();
	height = (unsigned int) image.TellHeight();

    setSize(width, height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
            Pixel p;

			p.Red = image(i,j)->Red;
			p.Green = image(i,j)->Green;
			p.Blue = image(i,j)->Blue;
            p.Alpha = image(i, j)->Alpha;

			pixels[i][j] = p;	

		}
	}
}

unsigned int BMPImage::getWidth() const
{   return width;  }

unsigned int BMPImage::getHeight() const
{   return height;  }

void BMPImage::setSize(unsigned int newWidth , unsigned int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0)
        throw std::out_of_range ("Size out of range. ");

    pixels.resize(newHeight, std::vector<Pixel> ());
    for (auto& row: pixels)
        row.resize(newWidth, defaultPixel);

    width = newWidth;
    height = newHeight;
}

Pixel BMPImage::getPixel(Position pos) const
{
    if (!checkPosition(pos))
        throw std::out_of_range ("Position out of range. ");

    return pixels[pos.y][pos.x];
}

void BMPImage::setPixel(Position pos, Pixel newPixel)
{
    if (!checkPosition(pos))
        throw std::out_of_range ("Position out of range. ");

    pixels[pos.y][pos.x] = newPixel;
}

void BMPImage::exportToPNGFile(std::string filename) const
{
    std::vector<unsigned char> image;
	for(auto row: pixels)
        for (auto pixel: row) {
            auto r =  (unsigned char) (pixel.Red);
            auto g =  (unsigned char) (pixel.Green);
            auto b =  (unsigned char) (pixel.Blue);
            auto a = (unsigned char) (pixel.Alpha);
            image.push_back(r);
            image.push_back(g);
            image.push_back(b);
            image.push_back(a);
	    }

	lodepng::encode(filename, image, width, height);
	
}

constexpr bool BMPImage::checkPosition(Position pos) const
{
    int i = pos.x;
    int j = pos.y;
    return (i < width && i >= 0 && j < height && j >= 0);
}