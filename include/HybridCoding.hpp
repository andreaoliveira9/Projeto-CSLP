#ifndef _HYBRID_CODING_H
#define _HYBRID_CODING_H

#include "Converter.hpp"
#include "Golomb.hpp"
#include "intraCoding.hpp"
#include "interCoding.hpp"
#include <vector>

using namespace cv;
using namespace std;

/**
 * @class HybridCoding
 * @brief Class for implementing hybrid video coding and decoding.
 *
 * This class uses a combination of motion-compensated predictive coding 
 * and transform coding to efficiently encode and decode video frames.
 */
class HybridEncoder {
private:
    VideoCapture video;
    int format;
    int videoWidth;
    int videoHeight;
    int frameNumber;
    int periodicity;
    int blockSize;
    int searchArea;
    int shift;

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
    HybridEncoder(string inputFile, int periodicity = 20, int searchArea = 4, int shift = 0);

    ~HybridEncoder();

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
    void encode(string outputFile);
};

/**
 * @class HybridCoding
 * @brief Class for implementing hybrid video coding and decoding.
 *
 * This class uses a combination of motion-compensated predictive coding 
 * and transform coding to efficiently encode and decode video frames.
 */
class HybridDecoder {
private:
    string inputFile;

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
    HybridDecoder(string inputFile);

    ~HybridDecoder();

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
    void decode(string outputFile);
};

#endif  // _HYBRID_CODING_H
