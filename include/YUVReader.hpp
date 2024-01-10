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

class YUVReader
{
private:
    string file_header;
    ifstream file;
    int height;
    int width;
    int frame_size;
    int n_frames;
    int read_frames = 0;
    bool assertFrame(char *buffer);
public:
    /**
     * @brief Construct a new YUVReader object
     * 
     * @param filename File name of the YUV file
     */
    YUVReader(string filename);

    /**
     * @brief Destroy the YUVReader object
     * 
     */
    ~YUVReader();

    /**
     * @brief Get the next frame object
     * 
     * @return bool that indicates if the end of the file has been reached
     */
    bool end_of_file();

    /**
     * @brief Get the next frame object
     * 
     * @return Mat that contains the next frame
     */
    Mat get_nextFrame();

    /**
     * @brief Get the next frame object
     * 
     * @return bool that indicates if the next frame exists
     */
    bool nextFrame_exists();

    /**
     * @brief Get the next frame object
     * 
     * @return int that indicates the number of frames in the file
     */
    int get_n_frames();

    /**
     * @brief Get the next frame object
     * 
     * @return int that indicates size of the frame
     */
    int get_frame_size();
};
#endif //YUVREADER_H