#ifndef _INTER_CODING_H
#define _INTER_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/** @class InterEncoder
 *  @brief Class for implementing inter-frame coding.
 *
 *  This class uses motion estimation and compensation techniques to efficiently encode video frames.
 */
class InterEncoder
{
private:
    int blockSize; ///< Size of the blocks used for motion estimation.
    int searchArea; ///< Size of the search area for motion estimation.
    int shift; ///< Shift value used for transform coding.
    GolombEncoder &GolombEncoder; ///< Reference to a GolombEncoder object for entropy coding.

public:
    /** @fn InterEncoder
     *  @brief Constructor for the InterEncoder class.
     *
     *  @param GolombEncoder Reference to a GolombEncoder object for entropy coding.
     *  @param blockSize Size of the blocks used for motion estimation.
     *  @param searchArea Size of the search area for motion estimation.
     *  @param shift Shift value used for transform coding (default is 0).
     */
    InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea, int shift = 0);

    /** @fn ~InterEncoder
     *  @brief Destructor for the InterEncoder class.
     */
    ~InterEncoder();

    /**
     * @brief Get the block size
     *
     * @return Block size
     */
    int getBlockSize() const;

    /**
     * @brief Get the block range
     *
     * @return Block range
     */
    int getSearchArea() const;

    /**
     * @brief Set the block size
     *
     * @param block_size New block size
     */
    void setBlockSize(int blockSize);

    /**
     * @brief Encode a frame
     *
     * @param old_frame Previous frame
     * @param new_frame Current frame
     * @return Result of the encoding
     */
    void encode(Mat &previousFrame, Mat &currentFrame);
};


/**
 * @class InterDecoder
 * @brief Class for implementing inter-frame decoding.
 *
 * This class uses motion compensation techniques to efficiently decode video frames.
 */
class InterDecoder
{
private:
    int blockSize; ///< Size of the blocks used for motion estimation.     
    int searchArea; ///< Size of the search area for motion estimation.
    int shift; ///< Shift value used for transform coding.             
    GolombDecoder &GolombDecoder; ///< Reference to a GolombDecoder object for entropy decoding.

public:
    /**
     * @brief Construct a new Inter Decoder object
     *
     * @param golomb Golomb decoder for decoding
     * @param block_size Size of the blocks for decoding
     * @param block_range Range of the blocks for decoding
     * @param shift Shift for decoding
     */
    InterDecoder(class GolombDecoder &GolombDecoder, int blockSize, int searchArea, int shift = 0);

    ~InterDecoder();
    
    /**
     * @brief Decode a frame
     *
     * @param previousFrame Previous frame
     * @param currentFrame Current frame
     * @return Result of the decoding
     */
    void decode(Mat &previousFrame, Mat &currentFrame);
};

#endif