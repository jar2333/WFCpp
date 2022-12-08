#include <BMPImage.h>

#include <lodepng.h>
#include <EasyBMP.h>

#include <filesystem>
namespace fs = std::filesystem;

#define LOG false

constexpr unsigned int defaultWidth = 5;
constexpr unsigned int defaultHeight = 5;

std::ostream& operator<<(std::ostream &os, const Pixel &p)
{
    return (os << "Red: " << int(p.Red) << " Green: " << int(p.Green) << " Blue: " << int(p.Blue)  << " Alpha: " << int(p.Alpha));
}

BMPImage::BMPImage()
{
    BMPImage(defaultWidth, defaultHeight);
}

BMPImage::BMPImage(unsigned int initWidth, unsigned int initHeight): 
    bitDepth(defaultBitDepth), verticalDPI(defaultVerticalDPI), horizontalDPI(defaultHorizontalDPI)
{
    setSize(initWidth, initHeight);
}

BMPImage::BMPImage(std::string filePath)
{
    fs::path p = filePath;
    FileType type;
    unsigned int width, height;

    if (p.extension() == ".png" || p.extension() == ".PNG")
        type = FileType::png;
    else if (p.extension() == ".bmp" || p.extension() == ".BMP")
        type = FileType::bmp;
    else
        throw std::invalid_argument("Invalid image file extension: " + p.extension().string() + " (we only support png or bmp). ");
		
    if (type == FileType::png) {
        std::vector<unsigned char> srcImg;
        std::vector<unsigned char> image;
        
        unsigned err = 0;

        if ((err = lodepng::load_file(srcImg, filePath)) != 0)
            throw std::runtime_error(std::string(lodepng_error_text(err)) + ": " + filePath);
        
        if ((err = lodepng::decode(image, width, height, srcImg)) != 0)
            throw std::runtime_error(std::string(lodepng_error_text(err)) + ": " + filePath);

        setSize(width, height);

        auto i = 0;
        for(unsigned int y = 0; y < height; y++) //the rows are stored inversed in bmp
            for(unsigned int x = 0; x < width; x++) {
                pixels[x][y].Red = image[i++];
                pixels[x][y].Green = image[i++];
                pixels[x][y].Blue = image[i++];
                pixels[x][y].Alpha = image[i++];
                pixels[x][y].count = 0;
            }
        
        bitDepth = defaultBitDepth;
        horizontalDPI = defaultHorizontalDPI;
        verticalDPI = defaultVerticalDPI;
    }
    else {
        BMP rawBMP;
	    rawBMP.ReadFromFile(filePath.c_str()); 
        width = (unsigned int) rawBMP.TellWidth();
	    height = (unsigned int) rawBMP.TellHeight();

        setSize(width, height);

        for (unsigned int y = 0; y < height; y++)
            for (unsigned int x = 0; x < width; x++){
                pixels[x][y] = rawBMP.GetPixel(x, y);
            }

        bitDepth = rawBMP.TellBitDepth();
        horizontalDPI = rawBMP.TellHorizontalDPI();
        verticalDPI = rawBMP.TellVerticalDPI();	
    }	
}

unsigned int BMPImage::getWidth() const noexcept
{   return pixels.size();  }

unsigned int BMPImage::getHeight() const noexcept
{   return pixels.size() > 0 ? pixels[0].size() : 0;  }

void BMPImage::setSize(unsigned int newWidth , unsigned int newHeight)
{
    pixels.resize(newWidth, std::vector<Pixel> ());
    for (auto& x: pixels)
        x.resize(newHeight, defaultPixel);
}

Pixel BMPImage::getPixel(Position pos) const
{
    if (!checkPosition(pos))
        throw std::out_of_range ("Position out of range. ");

    return pixels[pos.x][pos.y];
}

void BMPImage::setPixel(Position pos, Pixel newPixel)
{
    if (!checkPosition(pos))
        throw std::out_of_range ("Position out of range. ");

    pixels[pos.x][pos.y] = newPixel;
}

void BMPImage::exportToFile(std::string filename, FileType type) const
{
    auto width = getWidth();
    auto height = getHeight();

    if (type == FileType::png) {
        std::vector<unsigned char> image;
        for(unsigned int y = 0; y < height; y++)
            for (unsigned int x = 0; x < width; x++) {
                auto pixel = getPixel({x, y});
                auto r =  (unsigned char) (pixel.Red);
                auto g =  (unsigned char) (pixel.Green);
                auto b =  (unsigned char) (pixel.Blue);
                auto a =  (unsigned char) (pixel.Alpha);
                image.push_back(r);
                image.push_back(g);
                image.push_back(b);
                image.push_back(a);
            }

        int err = 0;
        if ((err = lodepng::encode(filename, image, width, height)) != 0)
            throw std::runtime_error(lodepng_error_text(err));
    } else {
        BMP res;
        res.SetSize(width, height);
        res.SetBitDepth(bitDepth);
        res.SetDPI(horizontalDPI, verticalDPI);
        for (unsigned int x = 0; x < width; x++)
            for (unsigned int y = 0; y < height; y++) {
                Pixel pixel = getPixel({x, y});
                RGBApixel rgbaPixel = { pixel.Blue, pixel.Green, pixel.Red, pixel.Alpha };
                res.SetPixel(x, y, rgbaPixel);
            }
        res.WriteToFile(filename.c_str());
    }
	
}

inline bool BMPImage::checkPosition(Position pos) const
{
    unsigned int x = pos.x;
    unsigned int y = pos.y;
    return (x < getWidth() && x >= 0 && y < getHeight() && y >= 0);
}