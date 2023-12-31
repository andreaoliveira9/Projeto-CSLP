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
    InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea, int shift = 0);

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