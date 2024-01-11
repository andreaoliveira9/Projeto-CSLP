#ifndef _HYBRID_CODING_H
#define _HYBRID_CODING_H

#include "Golomb.hpp"
#include "intraCoding.hpp"
#include "interCoding.hpp"
#include "FramesReader.hpp"
#include <vector>

using namespace cv;
using namespace std;

/**
 * @brief Converts YUV444 format to RGB format.
 * 
 * @param frame Input frame in YUV444 format.
 * @return Output frame in RGB format.
 */
Mat yuv444_to_rgb(Mat &frame);

/**
 * @class HybridEncoder
 * @brief Encodes video using hybrid coding techniques.
 * 
 * The HybridEncoder class is designed to encode video using a combination of 
 * motion-compensated predictive coding (inter-coding) and transform coding (intra-coding).
 */
class HybridEncoder {
private:
    FramesReader video; ///< Object for reading video frames.
    int format; ///< Format of the video.
    int videoWidth; ///< Width of the video frames.
    int videoHeight; ///< Height of the video frames.
    int frameNumber; ///< Number of frames in the video.
    int periodicity; ///< Number of frames between two consecutive intra-coded frames.
    int blockSize; ///< Current block size for motion estimation.
    int searchArea; ///< Size of the search area for motion estimation.
    int quantization1; ///< Quantization level for the first channel.
    int quantization2; ///< Quantization level for the second channel.
    int quantization3; ///< Quantization level for the third channel.
    double timeToCreateReader; ///< Time taken to create the YUV reader.
    double signalToNoiseRatio; ///< Signal-to-noise ratio of the encoded video.
    double bitsPerPixel; ///< Bits per pixel of the encoded video.

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
     * @param periodicity The number of frames between two consecutive intra-coded frames.
     * @param searchArea The size of the search area for motion estimation.
     * @param quantization1 The quantization level for the first channel.
     * @param quantization2 The quantization level for the second channel.
     * @param quantization3 The quantization level for the third channel.
     */
    HybridEncoder(string inputFile, int periodicity, int searchArea, int quantization1 = 255, int quantization2 = 255, int quantization3 = 255);

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
     * @brief Gets the signal-to-noise ratio of the encoded video.
     * 
     * @return The signal-to-noise ratio of the encoded video.
     */
    double getSignalToNoiseRatio();

    /**
     * @brief Gets the bits per pixel of the encoded video.
     * 
     * @return The bits per pixel of the encoded video.
     */
    double getBitsPerPixel();

    /**
     * @brief Encodes a video using hybrid coding.
     * 
     * Encodes video by comparing each frame with a reference frame and storing the differences. 
     * It alternates between intra and inter coding, depending on the periodicity.
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
    string inputFile; ///< Path to the encoded input video file.

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