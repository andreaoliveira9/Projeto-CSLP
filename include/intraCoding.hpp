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
 * Encodes video frames individually using the non-linear predictor of JPEG-LS technique and Golomb coding for entropy coding.
 */
class IntraEncoder {
private:
    GolombEncoder &golombEncoder; ///< GolombEncoder object for entropy coding.

public:
  /**
    * @brief Constructor for the IntraEncoder class.
    * @param golombEncoder Reference to a GolombEncoder object for entropy coding.
    */
  IntraEncoder(GolombEncoder &golombEncoder);
  
  /**
   * @brief Destructor for the IntraEncoder class.
   */
  ~IntraEncoder();

  /**
   * @brief Encodes a video frame using intra-frame encoding.
   * @param currentFrame The video frame to be encoded.
   * @param quantization1 The quantization level for the first channel.
   * @param quantization2 The quantization level for the second channel.
   * @param quantization3 The quantization level for the third channel.
   * @param totalSignal Total signal of the video.
   * @param totalNoise Total noise of the video.
   */
  void encode(Mat &currentFrame, int quantization1, int quantization2, int quantization3, int &totalSignal, int &totalNoise);

// ...
};

/**
 * @class IntraDecoder
 * @brief Class for implementing intra-frame decoding.
 *
 * Decodes video frames from their encoded state using the non-linear predictor of JPEG-LS technique and using 
 * Golomb coding for entropy decoding.
 */
class IntraDecoder {
private:
    GolombDecoder &golombDecoder; ///< GolombDecoder object for entropy decoding.

public:

    /**
     * @brief Constructor for the IntraDecoder class.
     * @param golombDecoder Reference to a GolombDecoder object for entropy decoding.
     */
  IntraDecoder(GolombDecoder &golombDecoder);
  

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