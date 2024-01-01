#ifndef _INTRA_CODING_H
#define _INTRA_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/**
 * @class IntraEncoder
 * @brief Class for implementing intra encoding.
 *
 * This class uses transform coding techniques to efficiently encode video frames.
 * It supports efficient encoding of video frames by considering spatial redundancies.
 * It also uses Golomb codes for entropy coding.
 */
class IntraEncoder {
private:
    int shift; ///< Shift value used for transform coding.
    GolombEncoder &golombEncoder; ///< Reference to a GolombEncoder object for entropy coding.

public:
    /** @fn IntraEncoder
     *  @brief Constructor for the IntraEncoder class.
     *
     *  @param golombEncoder Reference to a GolombEncoder object for entropy coding.
     *  @param shift Shift value used for transform coding (default is 0).
     */
  IntraEncoder(GolombEncoder &golombEncoder, int shift = 0);
  
    /** @fn ~IntraEncoder
     *  @brief Destructor for the IntraEncoder class.
     */
  ~IntraEncoder();

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
 * @class IntraDecoder
 * @brief Class for implementing intra decoding.
 *
 * This class uses transform coding techniques to efficiently decode video frames.
 * It supports efficient decoding of video frames by considering spatial redundancies.
 * It also uses Golomb codes for entropy coding.
 */
class IntraDecoder {
private:
    int shift; ///< Shift value used for transform coding.
    GolombDecoder &golombDecoder; ///< Reference to a GolombDecoder object for entropy coding.

public:

    /** @fn IntraDecoder
     *  @brief Constructor for the IntraDecoder class.
     *
     *  @param golombDecoder Reference to a GolombDecoder object for entropy coding.
     *  @param shift Shift value used for transform coding (default is 0).
     */
  IntraDecoder(GolombDecoder &golombDecoder, int shift = 0);
  

    /** @fn ~IntraDecoder
     *  @brief Destructor for the IntraDecoder class.
     */
  ~IntraDecoder();

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