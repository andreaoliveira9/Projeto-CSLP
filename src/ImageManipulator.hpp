#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class ImageManipulator
{
private:
    int width;
    int height;
    std::vector<unsigned char> pixels; // Stores image pixel data

public:
    ImageManipulator();
    ~ImageManipulator();

    bool loadPPM(const std::string &filename);
    bool savePPM(const std::string &filename);
    void copyImage(const ImageManipulator &source);
    int getWidth() const;
    int getHeight() const;
    unsigned char getRed(int x, int y) const;
    unsigned char getGreen(int x, int y) const;
    unsigned char getBlue(int x, int y) const;
    void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
};
