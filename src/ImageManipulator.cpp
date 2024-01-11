#include "ImageManipulator.hpp"

ImageManipulator::ImageManipulator() : width(0), height(0) {}
ImageManipulator::~ImageManipulator() {}

// Load an image from a PPM file
bool ImageManipulator::loadPPM(const std::string &filename)
{
    std::ifstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Failed to open PPM file: " << filename << endl;
        return false;
    }

    string format;
    file >> format;
    if (format != "P6")
    {
        cerr << "Unsupported PPM format: " << format << endl;
        return false;
    }

    file >> width >> height;
    int maxColor;
    file >> maxColor;
    file.ignore(); // Consume the newline character

    pixels.resize(width * height * 3);
    file.read(reinterpret_cast<char *>(&pixels[0]), pixels.size());

    return true;
}

// Save the image to a PPM file
bool ImageManipulator::savePPM(const std::string &filename)
{
    ofstream file(filename, ios::binary);
    if (!file)
    {
        cerr << "Failed to create PPM file: " << filename << endl;
        return false;
    }

    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";
    file.write(reinterpret_cast<char *>(&pixels[0]), pixels.size());

    return true;
}
// Copy the image pixel by pixel to another instance
void ImageManipulator::copyImage(const ImageManipulator &source)
{
    width = source.width;
    height = source.height;
    pixels = source.pixels;
}
// Accessors for image dimensions
int ImageManipulator::getWidth() const
{
    return width;
}

int ImageManipulator::getHeight() const
{
    return height;
}

// Accessors for pixel values (R, G, B)
unsigned char ImageManipulator::getRed(int x, int y) const
{
    return pixels[(y * width + x) * 3];
}

unsigned char ImageManipulator::getGreen(int x, int y) const
{
    return pixels[(y * width + x) * 3 + 1];
}

unsigned char ImageManipulator::getBlue(int x, int y) const
{
    return pixels[(y * width + x) * 3 + 2];
}

// Set pixel values (R, G, B)
void ImageManipulator::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
    pixels[(y * width + x) * 3] = red;
    pixels[(y * width + x) * 3 + 1] = green;
    pixels[(y * width + x) * 3 + 2] = blue;
}

