#include "HybridCoding.hpp"

HybridCoding::HybridCoding(BitStream *bitStream, int blockSize, int searchArea, int m, int periodicity = 0) {
    this->bitStream = bitStream;
    this->blockSize = blockSize;
    this->searchArea = searchArea;
    this->m = m;
    this->periodicity = periodicity;
}


void HybridCoding::encode(const Mat& referenceFrame, const Mat& currentFrame, int frameNum) {
    Golomb golombEncoder(bitStream, m);
    if (frameNum % periodicity == 0) {
        golombEncoder.encode(0);
        intraCoding pred;
        pred.encodeAndPredict(currentFrame, m, bitStream);
    } else {
        golombEncoder.encode(1);
        Mat currentBlock, possibleBlock, nearestMatrix;
        int lastSum = 100000;
        int currentSum = 0;
        int d_x = 0;
        int d_y = 0;
        int channel = 0;
        vector<Mat> currentMatrix, referenceMatrix;

        split(currentFrame, currentMatrix);
        split(referenceFrame, referenceMatrix);

        for (const auto& matrix : currentMatrix) {
            for (int row = 0; row < matrix.rows; row += blockSize) {
                for (int col = 0; col < matrix.cols; col += blockSize) {
                    currentBlock = Mat(matrix, Rect(col, row, blockSize, blockSize));

                    int startRow = row - searchArea;
                    int startCol = col - searchArea;
                    int endRow = row + searchArea + blockSize;
                    int endCol = col + searchArea + blockSize;

                    for (int i = startRow; i < endRow; i++) {
                        for (int j = startCol; j < endCol; j++) {
                            if (i < 0 || j < 0 || i + blockSize >= matrix.rows || j + blockSize >= matrix.cols) {
                                currentSum = 0;
                                continue;
                            }

                            possibleBlock = Mat(referenceMatrix[channel], Rect(j, i, blockSize, blockSize));

                            const uchar* currentPtr = currentBlock.ptr<uchar>(i - row);
                            const uchar* possiblePtr = possibleBlock.ptr<uchar>(0);

                            for (int a = 0; a < blockSize; a++) {
                                currentSum += abs(currentPtr[a] - possiblePtr[a]);
                            }

                            if (currentSum < lastSum) {
                                lastSum = currentSum;
                                d_x = i;
                                d_y = j;
                                nearestMatrix = possibleBlock;
                            }
                        }
                    }
                    lastSum = 100000;

                    golombEncoder.encode(d_x);
                    golombEncoder.encode(d_y);

                    for (int n = 0; n < blockSize; n++) {
                        const uchar* nearestPtr = nearestMatrix.ptr<uchar>(n);
                        const uchar* currentPtr = currentBlock.ptr<uchar>(n);

                        for (int m = 0; m < blockSize; m++) {
                            int z = static_cast<int>(nearestPtr[m]) - static_cast<int>(currentPtr[m]);
                            golombEncoder.encode(z);
                        }
                    }
                }
            }
            channel++;
        }
    }
}

Mat HybridCoding::decode(const Mat& previousFrame, int frameHeight, int frameWidth) {
    Mat result(frameHeight, frameWidth, CV_8UC3, Scalar(0, 0, 0));
    Golomb golombDecoder(bitStream, m);

    if (golombDecoder.decode() == 0) {
        intraCoding pred;
        pred.decodeAndReconstruct(bitStream, m, frameHeight, frameWidth);
    } else {
        vector<Mat> previousFrameChannels;
        split(previousFrame, previousFrameChannels);

        vector<Mat> res(3); // Initialize a vector to hold three channels
        for (int channel = 0; channel < 3; ++channel) {
            res[channel] = Mat(frameHeight, frameWidth, CV_8UC1, Scalar(0)); // Initialize each channel matrix
        }

        for (int channel = 0; channel < 3; ++channel) {
            for (int row = 0; row < frameHeight; row += blockSize) {
                for (int col = 0; col < frameWidth; col += blockSize) {
                    int d_x = golombDecoder.decode();
                    int d_y = golombDecoder.decode();

                    for (int n = 0; n < blockSize; ++n) {
                        const uchar* previousPtr = previousFrameChannels[channel].ptr<uchar>(d_x + n);
                        for (int m = 0; m < blockSize; ++m) {
                            int z = golombDecoder.decode();
                            int pixelValue = previousPtr[d_y + m] + z;
                            res[channel].at<uchar>(row + n, col + m) = pixelValue;
                        }
                    }
                }
            }
        }

        merge(res, result);
        imshow("Reconstructed Image", result);
    }
    return result;
}
