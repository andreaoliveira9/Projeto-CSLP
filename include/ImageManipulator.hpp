#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/**
 * @class ImageManipulator
 * @brief A class for loading, manipulating, and saving PPM image files.
 */
class ImageManipulator {
private:
    int width; ///< The width of the image.
    int height; ///< The height of the image.
    std::vector<unsigned char> pixels; ///< Stores image pixel data.

public:
    /**
     * @brief Constructor for the ImageManipulator class.
     */
    ImageManipulator();

    /**
     * @brief Destructor for the ImageManipulator class.
     */
    ~ImageManipulator();

    /**
     * @brief Load a PPM image from a file.
     *
     * @param filename The name of the PPM file to load.
     * @return true if the loading was successful, false otherwise.
     */
    bool loadPPM(const std::string &filename);

    /**
     * @brief Save the image as a PPM file.
     *
     * @param filename The name of the PPM file to save.
     * @return true if the saving was successful, false otherwise.
     */
    bool savePPM(const std::string &filename);

    /**
     * @brief Copy the content of another ImageManipulator object.
     *
     * @param source The source ImageManipulator object to copy from.
     */
    void copyImage(const ImageManipulator &source);

    /**
     * @brief Get the width of the image.
     *
     * @return The width of the image.
     */
    int getWidth() const;

    /**
     * @brief Get the height of the image.
     *
     * @return The height of the image.
     */
    int getHeight() const;

    /**
     * @brief Get the red component of a pixel at a specific position.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The red component of the pixel.
     */
    unsigned char getRed(int x, int y) const;

    /**
     * @brief Get the green component of a pixel at a specific position.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The green component of the pixel.
     */
    unsigned char getGreen(int x, int y) const;

    /**
     * @brief Get the blue component of a pixel at a specific position.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The blue component of the pixel.
     */
    unsigned char getBlue(int x, int y) const;

    /**
     * @brief Set the RGB components of a pixel at a specific position.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param red The new red component of the pixel.
     * @param green The new green component of the pixel.
     * @param blue The new blue component of the pixel.
     */
    void setPixel(int x, int y, unsigned char red, unsigned char green, unsigned char blue);
};
