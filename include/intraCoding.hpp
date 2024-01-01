#ifndef _INTRA_CODING_H
#define _INTRA_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/**
 * @class IntraEncoder
 * @brief Class for implementing intra-frame encoding.
 *
 * Encodes video frames individually using transform coding techniques, 
 * exploiting spatial redundancies within a frame and employing Golomb coding 
 * for entropy encoding.
 */
class IntraEncoder {
private:
    int shift; ///< Shift value used for transform coding.
    GolombEncoder &golombEncoder; ///< Reference to a GolombEncoder object for entropy coding.

public:
  /**
    * @brief Constructor for the IntraEncoder class.
    * @param golombEncoder Reference to a GolombEncoder object for entropy coding.
    * @param shift Shift value used for transform coding (default is 0).
    */
  IntraEncoder(GolombEncoder &golombEncoder, int shift = 0);
  
  /**
   * @brief Destructor for the IntraEncoder class.
   */
  ~IntraEncoder();

  /**
   * @brief Encodes a video frame using intra-frame encoding.
   * @param currentFrame The video frame to be encoded.
   */
  void encode(Mat &currentFrame);
};

/**
 * @class IntraDecoder
 * @brief Class for implementing intra-frame decoding.
 *
 * Decodes video frames from their encoded state using transform coding techniques,
 * reconstructing the original frame by exploiting spatial redundancies and using 
 * Golomb coding for entropy decoding.
 */
class IntraDecoder {
private:
    int shift; ///< Shift value used for transform coding.
    GolombDecoder &golombDecoder; ///< Reference to a GolombDecoder object for entropy decoding.

public:

    /**
     * @brief Constructor for the IntraDecoder class.
     * @param golombDecoder Reference to a GolombDecoder object for entropy decoding.
     * @param shift Shift value used for transform coding (default is 0).
     */
  IntraDecoder(GolombDecoder &golombDecoder, int shift = 0);
  

    /**
     * @brief Destructor for the IntraDecoder class.
     */
  ~IntraDecoder();

    /**
     * @brief Decodes an encoded video frame using intra-frame decoding.
     * @param currentFrame The video frame to be decoded and reconstructed.
     */
  void decode(Mat &currentFrame);
};

#endif 