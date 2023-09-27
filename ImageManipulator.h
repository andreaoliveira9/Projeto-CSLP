// ImageManipulator.h

#ifndef IMAGE_MANIPULATOR_H
#define IMAGE_MANIPULATOR_H

#include <string>
#include <vector>

class ImageManipulator
{
public:
    ImageManipulator();
    ~ImageManipulator();

    // Load an image from a PPM file
    bool loadPPM(const std::string &filename);

    // Save the image to a PPM file
    bool savePPM(const std::string &filename);

    // Copy the image pixel by pixel to another instance
    void copyImage(const ImageManipulator &source);

    // Accessors for image dimensions
    int getWidth() const;
    int getHeight() const;

    // Accessors for pixel values (R, G, B)
    unsigned char getRed(int x, int y) const;
    unsigned char getGreen(int x, int y) const;
    unsigned char getBlue(int x, int y) const;

    // Set pixel values (R, G, B)
    void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);

private:
    int width;
    int height;
    std::vector<unsigned char> pixels; // Stores image pixel data
};

#endif // IMAGE_MANIPULATOR_H
