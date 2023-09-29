// ImageManipulator.cpp

#include "ImageManipulator.h"
#include <fstream>
#include <iostream>

ImageManipulator::ImageManipulator() : width(0), height(0) {}

ImageManipulator::~ImageManipulator() {}

bool ImageManipulator::loadPPM(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open PPM file: " << filename << std::endl;
        return false;
    }

    std::string format;
    file >> format;
    if (format != "P6")
    {
        std::cerr << "Unsupported PPM format: " << format << std::endl;
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

bool ImageManipulator::savePPM(const std::string &filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to create PPM file: " << filename << std::endl;
        return false;
    }

    file << "P6\n";
    file << width << " " << height << "\n";
    file << "255\n";
    file.write(reinterpret_cast<char *>(&pixels[0]), pixels.size());

    return true;
}

void ImageManipulator::copyImage(const ImageManipulator &source)
{
    width = source.width;
    height = source.height;
    pixels = source.pixels;
}

int ImageManipulator::getWidth() const
{
    return width;
}

int ImageManipulator::getHeight() const
{
    return height;
}

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

void ImageManipulator::setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
    pixels[(y * width + x) * 3] = red;
    pixels[(y * width + x) * 3 + 1] = green;
    pixels[(y * width + x) * 3 + 2] = blue;
}
