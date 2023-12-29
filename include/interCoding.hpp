#ifndef _INTER_CODING_H
#define _INTER_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

class InterEncoder
{
private:
    int blockSize;       
    int searchArea;       
    int shift;             
    GolombEncoder &GolombEncoder; 

public:
    /**
     * @brief Construct a new Inter Encoder object
     *
     * @param golomb Golomb encoder for encoding
     * @param block_size Size of the blocks for encoding
     * @param block_range Range of the blocks for encoding
     * @param shift Shift for encoding
     */
    InterEncoder(GolombEncoder &GolombEncoder, int blockSize, int searchArea, int shift = 0);

    ~InterEncoder();

    /**
     * @brief Default constructor
     */
    InterEncoder() = default;

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
     * @brief Calculate the cost of encoding a block
     *
     * @param block Block to be encoded
     * @return Cost of encoding the block
     */
    float cost(Mat block);

    /**
     * @brief Encode a frame
     *
     * @param old_frame Previous frame
     * @param new_frame Current frame
     * @return Result of the encoding
     */
    void encode(Mat &previousFrame, Mat &currentFrame);
}

class InterDecoder
{
private:
    int blockSize;       
    int searchArea;       
    int shift;             
    GolombDecoder &GolombDecoder;

public:
    /**
     * @brief Construct a new Inter Decoder object
     *
     * @param golomb Golomb decoder for decoding
     * @param block_size Size of the blocks for decoding
     * @param block_range Range of the blocks for decoding
     * @param shift Shift for decoding
     */
    InterDecoder(GolombDecoder &GolombDecoder, int blockSize, int searchArea, int shift = 0);

    ~InterDecoder();

    /**
     * @brief Default constructor
     */
    InterDecoder() = default;
    
    /**
     * @brief Decode a frame
     *
     * @param previousFrame Previous frame
     * @param currentFrame Current frame
     * @return Result of the decoding
     */
    int decode(Mat &previousFrame, Mat &currentFrame);
}