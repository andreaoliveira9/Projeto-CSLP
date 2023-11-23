#ifndef _HYBRID_CODING_
#define _HYBRID_CODING_

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
    void encode(const Mat& referenceFrame, const Mat& currentFrame, int frameNum);
    Mat decode(const Mat& previousFrame, int frameHeight, int frameWidth);

private:
    int blockSize, searchArea, periodicity, m;
    BitStream *bitStream;
};

#endif  // _HYBRID_CODING_
