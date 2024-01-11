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

class FramesReader {
private:
    string fileHeader;
    ifstream file;
    int height;
    int width;
    int frameSize;
    int framesNumber;
    int readFrames = 0;

    bool assertFrame(char *buffer);
    void openFile(string filename);
    void readHeader();
    int countFrames();
    void handleFrameReadError();

public:
    FramesReader(string filename);
    ~FramesReader();

    bool endOfFile();
    Mat getNextFrame();
    bool nextFrameExists();
    int getNumFrames();
    int getFrameSize();
};

#endif // YUVREADER_H
