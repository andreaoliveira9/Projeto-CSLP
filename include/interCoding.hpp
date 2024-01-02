#ifndef _INTER_CODING_H
#define _INTER_CODING_H

#include <iostream>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/**
 * @class InterEncoder
 * @brief Class for implementing inter-frame encoding.
 *
 * Utilizes motion estimation and compensation techniques to efficiently encode video frames
 * by predicting frame content based on previous frames, thereby reducing temporal redundancy.
 */
class InterEncoder
{
private:
    int blockSize; ///< Size of the blocks used for motion estimation.
    int searchArea; ///< Size of the search area for motion estimation.
    int shift; ///< Shift value used for transform coding.
    GolombEncoder &GolombEncoder; ///< Reference to a GolombEncoder object for entropy coding.

public:
    /**
     * @brief Constructor for the InterEncoder class.
     * @param golombEncoder Reference to a GolombEncoder object for entropy coding.
     * @param blockSize Size of the blocks used for motion estimation.
     * @param searchArea Size of the search area for motion estimation.
     * @param shift Shift value used for transform coding (default is 0).
     */
    InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea, int shift = 0);

    /**
     * @brief Destructor for the InterEncoder class.
     */
    ~InterEncoder();

    /**
     * @brief Set the size of the blocks used for motion estimation.
     * @param blockSize New size of the blocks.
     */
    void setBlockSize(int blockSize);

    /**
     * @brief Encode a frame using inter-frame coding.
     * @param previousFrame The previous video frame for reference.
     * @param currentFrame The current video frame to be encoded.
     */
    void encode(Mat &previousFrame, Mat &currentFrame);

    void findNearestBlock(Mat &previousFrame, Mat &currentBlock, int startRow, int startCol, int endRow, int endCol, int &d_x, int &d_y, int &lastSum, Mat &blocksDifferences, Mat &nearestBlock, int channelsNumber);
};


/**
 * @class InterDecoder
 * @brief Class for implementing inter-frame decoding.
 *
 * Utilizes motion compensation techniques to efficiently decode video frames
 * by reconstructing frame content based on previous frames, thereby reducing temporal redundancy.
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
     * @brief Constructor for the InterDecoder class.
     * @param golombDecoder Reference to a GolombDecoder object for entropy decoding.
     * @param blockSize Size of the blocks used for motion compensation.
     * @param searchArea Size of the search area for motion compensation.
     * @param shift Shift value used for transform coding (default is 0).
     */
    InterDecoder(class GolombDecoder &GolombDecoder, int blockSize, int searchArea, int shift = 0);
    
    /**
     * @brief Destructor for the InterDecoder class.
     */
    ~InterDecoder();
    
    /**
     * @brief Decode a frame using inter-frame decoding.
     * @param previousFrame The reference video frame from which the current frame will be predicted.
     * @param currentFrame The current video frame to be decoded and reconstructed.
     */
    void decode(Mat &previousFrame, Mat &currentFrame);
};

#endif