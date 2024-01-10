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
    YUVReader(string filename);
    ~YUVReader();

    bool end_of_file();
    Mat get_nextFrame();
    bool nextFrame_exists();
    int get_n_frames();
    int get_frame_size();
};
#endif //YUVREADER_H