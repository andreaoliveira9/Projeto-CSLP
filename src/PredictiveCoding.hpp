#ifndef _PREDICTIVE_ENCODING_
#define _PREDICTIVE_ENCODING_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

class PredictiveCoding {
public:
  void encodeAndPredict(Mat frame, int m, BitStream *bs);
  Mat decodeAndReconstruct(BitStream *bs, int m, int rows, int cols);
};

#endif 