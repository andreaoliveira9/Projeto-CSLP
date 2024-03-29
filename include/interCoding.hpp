#ifndef _INTER_CODING_H
#define _INTER_CODING_H

#include <iostream>
#include <unistd.h>
#include <queue>
#include "opencv2/opencv.hpp"
#include "Golomb.hpp"

using namespace cv;
using namespace std;

/**
 * @class InterEncoder
 * @brief Class for implementing inter-frame encoding.
 *
 * Utilizes motion estimation and compensation techniques to efficiently encode video frames
 * by predicting frame content based on previous frames.
 */
class InterEncoder
{
private:
    int blockSize; ///< Size of the blocks used for motion estimation.
    int searchArea; ///< Size of the search area for motion estimation.
    GolombEncoder &GolombEncoder; ///< GolombEncoder object for entropy coding.

    /**
     * @brief Find the block in the previous frame that is most similar to the current block.
     * @param previousFrame The previous video frame for reference.
     * @param currentBlock The current block to be encoded.
     * @param startRow The starting row of the search area.
     * @param startCol The starting column of the search area.
     * @param endRow The ending row of the search area.
     * @param endCol The ending column of the search area.
     * @param d_x The horizontal displacement of the block in the previous frame.
     * @param d_y The vertical displacement of the block in the previous frame.
     * @param lastSum The sum of the absolute differences of the previous block and the current block.
     * @param blocksDifferences Matrix containing the absolute differences of the previous block and the current block.
     * @param fewestDifferences Matrix containing the absolute differences of the previous block and the current block with the fewest differences.
     * @param channelsNumber Number of channels of the video.
    */
    void findNearestBlock(Mat &previousFrame, Mat &currentBlock, int startRow, int startCol, int endRow, int endCol, int &d_x, int &d_y, int &lastSum, Mat &blocksDifferences, Mat &fewestDifferences, int channelsNumber);

    /**
     * @brief Encode the motion vectors of the current frame.
     * @param previousFrame The previous video frame for reference.
     * @param currentFrame The current video frame to be encoded.
     * @param auxiliarFrame An auxiliar frame used for motion compensation.
     * @param row The starting row of the current block.
     * @param col The starting column of the current block.
     * @param channelsNumber Number of channels of the video.
     * @param vectorCoordinates Queue containing the coordinates of the motion vectors encoded.
     * @param quantization1 The quantization level for the first channel.
     * @param quantization2 The quantization level for the second channel.
     * @param quantization3 The quantization level for the third channel.
     * @param totalSignal Total signal of the video.
     * @param totalNoise Total noise of the video.
     */
    void encodeAndApplyMotionCompenstation(Mat &previousFrame, Mat &currentFrame, Mat &auxiliarFrame, int row, int col, int channelsNumber, std::queue<int> &vectorCoordinates, int quantization1, int quantization2, int quantization3, int &totalSignal, int &totalNoise);

public:
    /**
     * @brief Constructor for the InterEncoder class.
     * @param golombEncoder Reference to a GolombEncoder object for entropy coding.
     * @param blockSize Size of the blocks used for motion estimation.
     * @param searchArea Size of the search area for motion estimation.
     */
    InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea);

    /**
     * @brief Destructor for the InterEncoder class.
     */
    ~InterEncoder();
    
    void setBlockSize(int blockSize);
    /**
     * @brief Encode a frame using inter-frame coding.
     * @param previousFrame The previous video frame for reference.
     * @param currentFrame The current video frame to be encoded.
     * @param quantization1 The quantization level for the first channel.
     * @param quantization2 The quantization level for the second channel.
     * @param quantization3 The quantization level for the third channel.
     * @param totalSignal Total signal of the video.
     * @param totalNoise Total noise of the video.
     */
    void encode(Mat &previousFrame, Mat &currentFrame, int quantization1, int quantization2, int quantization3, int &totalSignal, int &totalNoise);
};


/**
 * @class InterDecoder
 * @brief Class for implementing inter-frame decoding.
 *
 * Utilizes motion compensation techniques to efficiently decode video frames
 * by reconstructing frame content based on previous frames.
 */
class InterDecoder
{
private:
    int blockSize; ///< Size of the blocks used for motion estimation.
    int searchArea; ///< Size of the search area for motion estimation.
    GolombDecoder &GolombDecoder; ///< GolombDecoder object for entropy decoding.

public:
    /**
     * @brief Constructor for the InterDecoder class.
     * @param golombDecoder Reference to a GolombDecoder object for entropy decoding.
     * @param blockSize Size of the blocks used for motion compensation.
     * @param searchArea Size of the search area for motion compensation.
     */
    InterDecoder(class GolombDecoder &GolombDecoder, int blockSize, int searchArea);
    
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