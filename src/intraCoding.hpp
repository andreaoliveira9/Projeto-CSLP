#ifndef _INTRA_ENCODING_
#define _INTRA_ENCODING_

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;


/**
 * @class intraCoding
 * @brief Class for implementing intra encoding and decoding.
 *
 * This class utilises methods of intra encoding and decoding,
 * which are common techniques in image and video compression.
 */
class intraCoding {
public:
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
  void encodeAndPredict(Mat frame, int m, BitStream *bs);

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
  Mat decodeAndReconstruct(BitStream *bs, int m, int rows, int cols);
};

#endif 