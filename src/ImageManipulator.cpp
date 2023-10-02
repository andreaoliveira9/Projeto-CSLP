#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class ImageManipulator
{
private:
    int width;
    int height;
    std::vector<unsigned char> pixels; // Stores image pixel data
public:
    ImageManipulator() : width(0), height(0) {}
    ~ImageManipulator() {}

    // Load an image from a PPM file
    bool loadPPM(const std::string &filename)
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

    // Save the image to a PPM file
    bool savePPM(const std::string &filename)
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
    // Copy the image pixel by pixel to another instance
    void copyImage(const ImageManipulator &source)
    {
        width = source.width;
        height = source.height;
        pixels = source.pixels;
    }
    // Accessors for image dimensions
    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    // Accessors for pixel values (R, G, B)
    unsigned char getRed(int x, int y) const
    {
        return pixels[(y * width + x) * 3];
    }

    unsigned char getGreen(int x, int y) const
    {
        return pixels[(y * width + x) * 3 + 1];
    }

    unsigned char getBlue(int x, int y) const
    {
        return pixels[(y * width + x) * 3 + 2];
    }

    // Set pixel values (R, G, B)
    void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue)
    {
        pixels[(y * width + x) * 3] = red;
        pixels[(y * width + x) * 3 + 1] = green;
        pixels[(y * width + x) * 3 + 2] = blue;
    }
};
