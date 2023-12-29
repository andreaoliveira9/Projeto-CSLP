#ifndef _INTRA_CODING_H
#define _INTRA_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/**
 * @class intraCoding
 * @brief Class for implementing intra encoding and decoding.
 *
 * This class utilises methods of intra encoding and decoding,
 * which are common techniques in image and video compression.
 */
class intraEncoder {
private:
    int shift;
    GolombEncoder &golombEncoder;

public:
  intraEncoder(GolombEncoder &golombEncoder, int shift = 0);
  
  ~intraEncoder();

  /**
   * @brief Encodes a frame using intra encoding and stores the result.
   * 
   * This method applies intra encoding to a video frame and stores
   * the results in a bit stream. It utilizes the parameter m for
   * the intra encoding process.
   * 
   * @param frame Video frame to be encoded.
   * @param m Parameter for the Golomb enocde.
   * @param bs Pointer to the bit stream where the encoded data will be stored.
   */
  void encode(Mat &currentFrame);
};

/**
 * @class intraCoding
 * @brief Class for implementing intra encoding and decoding.
 *
 * This class utilises methods of intra encoding and decoding,
 * which are common techniques in image and video compression.
 */
class intraDecoder {
private:
    int shift;
    GolombDecoder &golombDecoder;

public:
  intraDecoder(GolombDecoder &golombDecoder, int shift = 0);
  
  ~intraDecoder();

    /**
   * @brief Decodes a bit stream and reconstructs the video frame.
   *
   * This method reads an encoded bit stream and reconstructs the video frame
   * using intra decoding. The parameter m is used for the intra
   * decoding process. The dimensions of the video frame (rows and cols) need
   * to be specified for accurate reconstruction.
   * 
   * @param bs Pointer to the encoded bit stream.
   * @param m Parameter for the Golomb decode.
   * @param rows Number of rows in the frame to be reconstructed.
   * @param cols Number of columns in the frame to be reconstructed.
   * @return Mat Decoded video frame.
   */
  void decode(Mat &currentFrame);
};

#endif 