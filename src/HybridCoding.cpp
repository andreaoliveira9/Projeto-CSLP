#include "HybridCoding.hpp"

HybridCoding::HybridCoding(BitStream *bitStream, int blockSize, int searchArea, int periodicity, int m) {
    this->bitStream = bitStream;
    this->blockSize = blockSize;
    this->searchArea = searchArea;
    this->periodicity = periodicity;
    this->m = m;
}

void HybridCoding::encode(Mat referenceFrame, Mat currentFrame, int frameNum) {
    if (frameNum % periodicity == 0) {
        PredictiveCoding pred;
        pred.encodeAndPredict(currentFrame, m, bitStream);
    } else {
        Golomb golombEncoder(bitStream, m);
        Mat currentBlock, possibleBlock, nearestMatrix;
        int lastSum = 100000;
        int currentSum = 0;
        int d_x = 0;
        int d_y = 0;
        int channel = 0;
        vector<Mat> currentMatrix;
        split(currentFrame, currentMatrix);
        vector<Mat> referenceMatrix;
        split(referenceFrame, referenceMatrix);

        for (Mat matrix : currentMatrix) {
            for (int row = 0; row < matrix.rows; row += blockSize) {
                for (int col = 0; col < matrix.cols; col += blockSize) {
                    currentBlock = Mat(matrix, Rect(col, row, blockSize, blockSize));

                    int startRow = row - searchArea;
                    int startCol = col - searchArea;
                    int endRow = row + searchArea + blockSize;
                    int endCol = col + searchArea + blockSize;

                    for (int i = startRow; i < endRow; i++) {
                        for (int j = startCol; j < endCol; j++) {
                            if (i < 0 || j < 0 || i + blockSize > matrix.rows || j + blockSize > matrix.cols) {
                                currentSum = 0;
                                continue;
                            }

                            possibleBlock = Mat(referenceMatrix[channel], Rect(j, i, blockSize, blockSize));

                            for (int a = 0; a < blockSize; a++) {
                                for (int b = 0; b < blockSize; b++) {
                                    currentSum = currentSum + abs(((int)currentBlock.at<uchar>(a, b)-(int)possibleBlock.at<uchar>(a, b)));
                                }
                            }

                            if (currentSum < lastSum) {
                                lastSum = currentSum;
                                d_x = i;
                                d_y = j;
                                nearestMatrix = possibleBlock;
                            }
                        }
                    }
                    lastSum = 10000;

                    golombEncoder.encode(row - d_x);
					golombEncoder.encode(col - d_y);

                    for(int n = 0; n < blockSize; n++){
                        for(int m = 0; m < blockSize; m++){
                            int z = (int)((int)nearestMatrix.at<uchar>(n, m) - (int)currentBlock.at<uchar>(n, m));
                            golombEncoder.encode(z);
                        }
                    }
                }
            }
            channel++;
        }
    }
}

Mat HybridCoding::decode(Mat previousFrame, int frameHeight, int frameWidth, int frameNum) {
    Mat result(frameHeight, frameWidth, CV_8UC3, Scalar(0, 0, 0));
    Golomb golombDecoder(bitStream, m);

    if (frameNum % periodicity == 0) {
        PredictiveCoding pred;
        result = pred.decodeAndReconstruct(bitStream, m, frameHeight, frameWidth);
    } else {
        vector<Mat> previousFrameChannels;
        split(previousFrame, previousFrameChannels);

        vector<Mat> res(3); // Initialize a vector to hold three channels
        for (int channel = 0; channel < 3; ++channel) {
            res[channel] = Mat(frameHeight, frameWidth, CV_8UC1, Scalar(0)); // Initialize each channel matrix
        }

        for (int row = 0; row < frameHeight; row += blockSize) {
            for (int col = 0; col < frameWidth; col += blockSize) {
                // Decode the motion vectors
                int rowDiff = golombDecoder.decode();
                int colDiff = golombDecoder.decode();
                int d_x = row - rowDiff;
                int d_y = col - colDiff;

                for (int channel = 0; channel < 3; ++channel) {
                    for (int n = 0; n < blockSize; ++n) {
                        for (int m = 0; m < blockSize; ++m) {
                            int z = golombDecoder.decode();
                            int pixelValue = previousFrameChannels[channel].at<uchar>(d_x + n, d_y + m) + z;
                            // Avoid out-of-bounds access
                            if (d_x + n < frameHeight && d_y + m < frameWidth) {
                                res[channel].at<uchar>(d_x + n, d_y + m) = pixelValue;
                            }
                        }
                    }
                }
            }
        }

        merge(res, result);
    }
    imshow("Frame", result);
    return result;
}

