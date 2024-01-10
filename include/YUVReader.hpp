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
     * @param filename 
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
     * @return Mat 
     */
    bool end_of_file();

    /**
     * @brief Get the next frame object
     * 
     * @return Mat 
     */
    Mat get_nextFrame();

    /**
     * @brief Get the next frame object
     * 
     * @return Mat 
     */
    bool nextFrame_exists();

    /**
     * @brief Get the next frame object
     * 
     * @return Mat 
     */
    int get_n_frames();

    /**
     * @brief Get the next frame object
     * 
     * @return Mat 
     */
    int get_frame_size();
};
#endif //YUVREADER_H