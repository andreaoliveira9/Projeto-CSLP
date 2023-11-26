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

/**
 * @class HybridCoding
 * @brief Class for implementing hybrid video coding and decoding.
 *
 * This class uses a combination of motion-compensated predictive coding 
 * and transform coding to efficiently encode and decode video frames.
 */
class HybridCoding {
public:
    /**
     * @brief Constructs a HybridCoding object.
     * 
     * Initialises the hybrid coding system with parameters for video encoding and decoding.
     * 
     * @param bitStream Pointer to the BitStream object for reading or writing encoded data.
     * @param blockSize Size of the block for motion estimation and compensation.
     * @param searchArea Area around the block where motion is estimated.
     * @param periodicity Interval intra and inter encoding.
     * @param m Parameter for the Golomb code.
     */
    HybridCoding(BitStream *bitStream, int blockSize, int searchArea, int periodicity, int m);

    /**
     * @brief Encodes a video frame using hybrid coding.
     * 
     * Encodes the current frame by comparing it with a reference 
     * frame and storing the differences, periodically alternating between intra and inter coding.
     * 
     * @param referenceFrame The reference frame for motion estimation.
     * @param currentFrame The current frame to be encoded.
     * @param frameNum The number of the current frame in the sequence.
     */
    void encode(const Mat& referenceFrame, const Mat& currentFrame, int frameNum);

    /**
     * @brief Decodes an encoded frame.
     *
     * Reconstructs a video frame from the encoded data using the previous frame as a reference, 
     * alternately employing inter and intra coding based on the initial bit.
     * 
     * @param previousFrame The previous frame used for reference in decoding.
     * @param frameHeight Height of the frame to be decoded.
     * @param frameWidth Width of the frame to be decoded.
     * @return Mat The decoded video frame.
     */
    Mat decode(const Mat& previousFrame, int frameHeight, int frameWidth);

private:
    int blockSize, searchArea, periodicity, m;  ///< Parameters for motion estimation and compensation.
    BitStream *bitStream;                       ///< Pointer to the bit stream for encoded data.
};

#endif  // _HYBRID_CODING_
