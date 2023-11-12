#ifndef _HYBRID_ENCODER_
#define _HYBRID_ENCODER_

#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class HybridCoding {
public:
    HybridCoding(BitStream *bitStream, int blockSize, int searchArea, int periodicity, int m);
    void encode(Mat referenceFrame, Mat currentFrame, int frameNum);
    Mat decode(Mat previousFram, int frameHeight, int frameWidth, int frameNum);

private:
    int blockSize, searchArea, periodicity, m;
    BitStream *bitStream;
    int frameNum = 1;
};

#endif  // HYBRID_ENCODER_HPP
