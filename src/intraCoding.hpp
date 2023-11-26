#ifndef _INTRA_ENCODING_
#define _INTRA_ENCODING_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


/**
 * @class PredictiveCoding
 * @brief Class for implementing predictive encoding and decoding.
 *
 * This class utilises methods of predictive encoding and decoding,
 * which are common techniques in image and video compression.
 */
class intraCoding {
public:
  /**
   * @brief Encodes a frame using predictive encoding and stores the result.
   * 
   * This method applies predictive encoding to a video frame and stores
   * the results in a bit stream.
   * 
   * @param frame Video frame to be encoded.
   * @param m Parameter for the predictive encoding.
   * @param bs Pointer to the bit stream where the encoded data will be stored.
   */
  void encodeAndPredict(Mat frame, int m, BitStream *bs);

    /**
   * @brief Decodes a bit stream and reconstructs the video frame.
   *
   * This method reads an encoded bit stream and reconstructs the video frame
   * using predictive decoding.
   * 
   * @param bs Pointer to the encoded bit stream.
   * @param m Parameter for the predictive decoding.
   * @param rows Number of rows in the frame to be reconstructed.
   * @param cols Number of columns in the frame to be reconstructed.
   * @return Mat Decoded video frame.
   */
  Mat decodeAndReconstruct(BitStream *bs, int m, int rows, int cols);
};

#endif 