#include <opencv2/opencv.hpp>
#include <iostream>

#include "BitStream.cpp"
#include "Golomb.cpp"

using namespace std;
using namespace cv;

class PredictiveCoding {
public:
  void encodeAndPredict(Mat frame, int m, BitStream *bs);
  int decodeAndReconstruct(BitStream *bs, int m, int rows, int cols);
};