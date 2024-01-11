#ifndef YUVREADER_H
#define YUVREADER_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;
using namespace cv;

/**
 * @brief Class for reading frames from a YUV file.
 */
class FramesReader {
private:
    string fileHeader; /**< Header information of the YUV file. */
    ifstream file; /**< Input file stream for reading the YUV file. */
    int height; /**< Height of each frame in pixels. */
    int width; /**< Width of each frame in pixels. */
    int framesNumber; /**< Total number of frames in the YUV file. */
    int readedFrames = 0; /**< Number of frames already read. */

    /**
     * @brief Count the total number of frames in the YUV file.
     * @return Total number of frames.
     */
    int countFrames();

public:
    /**
     * @brief Constructor for FramesReader.
     * @param filename Path to the YUV file.
     */
    FramesReader(string filename);

    /**
     * @brief Destructor for FramesReader.
     */
    ~FramesReader();

    /**
     * @brief Check if the end of the file has been reached.
     * @return True if the end of the file is reached, otherwise false.
     */
    bool endOfFile();

    /**
     * @brief Get the next frame from the YUV file.
     * @return The next frame as a Mat object.
     */
    Mat getNextFrame();

    /**
     * @brief Check if there is another frame available for reading.
     * @return True if there is another frame, otherwise false.
     */
    bool nextFrameExists();

    /**
     * @brief Get the total number of frames in the YUV file.
     * @return Total number of frames.
     */
    int getNumFrames();

    /**
     * @brief Get the size of each frame in the YUV file.
     * @return Size of each frame.
     */
    int getFrameSize();
};

#endif // YUVREADER_H
