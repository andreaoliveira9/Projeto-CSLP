#ifndef _HYBRID_CODING_H
#define _HYBRID_CODING_H

#include "Converter.hpp"
#include "Golomb.hpp"
#include "intraCoding.hpp"
#include "interCoding.hpp"
#include "YUVReader.hpp"
#include <vector>

using namespace cv;
using namespace std;

/**
 * @class HybridEncoder
 * @brief Encodes video using hybrid coding techniques.
 * 
 * The HybridEncoder class is designed to encode video using a combination of 
 * motion-compensated predictive coding (inter-coding) and transform coding (intra-coding). 
 * It supports efficient encoding by exploiting both spatial and temporal redundancies.
 */
class HybridEncoder {
private:
    YUVReader video;
    int format; 
    int videoWidth; 
    int videoHeight; 
    int frameNumber; 
    int periodicity; 
    int blockSize; 
    int searchArea; 
    int quantization1;
    int quantization2;
    int quantization3;
    double timeToCreateReader;

    /**
     * @brief Sets the best block size for motion estimation.
     * 
     * Sets the best block size for motion estimation, based on the current frame and the previous frame.
     * 
     * @param currentFrame The current frame being processed.
     * @param GolombEncoder The Golomb encoder used for encoding the video.
     * @param interEncoder The inter encoder used for encoding the video.
     */
    void setBestBlockSize(Mat &currentFrame, GolombEncoder &GolombEncoder, InterEncoder &interEncoder);

public:
    /**
     * @brief Constructor for HybridEncoder.
     * 
     * Initializes the hybrid encoder with the necessary parameters for video encoding.
     * 
     * @param inputFile The path to the input video file.
     * @param periodicity The frequency of I-frames in the video sequence.
     * @param searchArea The size of the area around the block where motion is estimated.
     * @param shift The shift value used for transform coding.
     */
    HybridEncoder(string inputFile, int periodicity = 20, int searchArea = 4, int quantization1 = 255, int quantization2 = 255, int quantization3 = 255);

    /**
     * @brief Destructor for HybridEncoder.
     */

    ~HybridEncoder();

    /**
     * @brief Gets the number of frames in the video.
     * 
     * @return The number of frames in the video.
     */
    int getFrameNumber();

    /**
     * @brief Gets the time taken to create the YUV reader.
     * 
     * @return The time taken to create the YUV reader.
     */
    double getTimeToCreateReader();

    /**
     * @brief Encodes a video using hybrid coding.
     * 
     * Encodes video by comparing each frame with a reference frame and storing the differences. 
     * It alternates between intra and inter coding, depending on the frame position and periodicity.
     * 
     * @param outputFile The path to the output file where the encoded data will be saved.
     */
    void encode(string outputFile);

};

/**
 * @class HybridDecoder
 * @brief Decodes video that was encoded using hybrid coding techniques.
 * 
 * The HybridDecoder class is responsible for decoding video that was encoded by the HybridEncoder class. 
 * It uses motion-compensated predictive coding and transform coding to reconstruct the original video frames.
 */
class HybridDecoder {
private:
    string inputFile; 

public:
    /**
     * @brief Constructor for HybridDecoder.
     * 
     * Initializes the hybrid decoder with the necessary parameters for video decoding.
     * 
     * @param inputFile The path to the encoded input video file.
     */
    HybridDecoder(string inputFile);

    /**
     * @brief Destructor for HybridDecoder.
     */

    ~HybridDecoder();

    /**
     * @brief Decodes an encoded video.
     * 
     * Reconstructs the video frames from the encoded data, using the previous frame as a reference. 
     * It alternates between inter and intra coding methods during the decoding process.
     * 
     * @param outputFile The path to the output file where the decoded video will be saved.
     */
    void decode(string outputFile);
};

#endif  // _HYBRID_CODING_H