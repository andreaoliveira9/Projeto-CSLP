#include "interCoding.hpp"
#include <unistd.h>

InterEncoder::InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea, int shift) : GolombEncoder(GolombEncoder), blockSize(blockSize), searchArea(searchArea), shift(shift)
{
}

InterEncoder::~InterEncoder()
{
}

void InterEncoder::setBlockSize(int blockSize)
{
    this->blockSize = blockSize;
}

void InterEncoder::encode(Mat &previousFrame, Mat &currentFrame)
{
    int lastSum;
    int mGolombParameter;
    int error;
    int d_x;
    int d_y;
    int startCol;
    int startRow;
    int endCol;
    int endRow;
    Mat blocksDifferences;
    Mat nearestBlock;
    Mat auxiliarFrame;
    Mat currentBlock;

    int count = 0;
    int max_x = currentFrame.cols - this->blockSize;
    int max_y = currentFrame.rows - this->blockSize;
    int channelsNumber = currentFrame.channels();
    int locations[(currentFrame.rows * currentFrame.cols) / (this->blockSize * this->blockSize) * 2];

    if (channelsNumber == 3) {
        blocksDifferences = Mat::zeros(this->blockSize, this->blockSize, CV_16SC3);
        auxiliarFrame = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC3);
    } else if (channelsNumber == 1) {
        blocksDifferences = Mat::zeros(this->blockSize, this->blockSize, CV_16SC1);
        auxiliarFrame = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC1);
    }

    // Iterate through current frame's blocks.
    for (int row = 0; row <= max_y; row += this->blockSize)
    {
        for (int col = 0; col <= max_x; col += this->blockSize)
        {
            lastSum = 10000000;

            currentBlock = Mat(currentFrame, Rect(col, row, this->blockSize, this->blockSize));

            startRow = row - this->searchArea;
            startCol = col - this->searchArea;
            endRow = row + this->searchArea;
            endCol = col + this->searchArea;

            if (startRow < 0) {
                startRow = 0;
            }
            if (startCol < 0) {
                startCol = 0;
            }
            if (endRow > max_y) {
                endRow = max_y;
            }
            if (endCol > max_x) {
                endCol = max_x;
            }

            findNearestBlock(previousFrame, currentBlock, startRow, startCol, endRow, endCol, d_x, d_y, lastSum, blocksDifferences, nearestBlock, channelsNumber);
            
            // Store blocks coordinates.
            locations[count++] = d_x;
            locations[count++] = d_y;

            // Store error between blocks
            Rect rect(col, row, this->blockSize, this->blockSize);
            nearestBlock.copyTo(auxiliarFrame(rect));
        }
    }
    // Calculate optimal m...
    mGolombParameter = GolombEncoder.optimal_m(auxiliarFrame);

    // If m stays the same encode 0, otherwise, encode m
    if (GolombEncoder.get_m() == mGolombParameter) {
        GolombEncoder.encode(0);
    } else {
        GolombEncoder.encode(mGolombParameter);
        GolombEncoder.set_m(mGolombParameter);
    }

    count = 0;
    
    for (int row = 0; row <= max_y; row += this->blockSize) {
        for (int col = 0; col <= max_x; col += this->blockSize) {
            GolombEncoder.encode(locations[count++]);
            GolombEncoder.encode(locations[count++]);
            for (int i = row; i < row + this->blockSize; i++) {
                for (int j = col; j < col + this->blockSize; j++) {
                    for (int channel = 0; channel < channelsNumber; channel++) {
                        error = auxiliarFrame.ptr<short>(i, j)[channel];

                        if (error < 0) {
                            error = -1 * (abs(error) >> this->shift);
                        } else {
                            error >>= this->shift;
                        }

                        GolombEncoder.encode(error);

                        if (error < 0) {
                            error = -1 * (abs(error) << this->shift);
                        } else {
                            error <<= this->shift;
                        }

                        currentFrame.ptr<uchar>(i, j)[channel] = error + previousFrame.ptr<uchar>(i, j)[channel];
                    }
                }
            }
        }
    }
}

void InterEncoder::findNearestBlock(Mat &previousFrame, Mat &currentBlock, int startRow, int startCol, int endRow, int endCol, int &d_x, int &d_y, int &lastSum, Mat &blocksDifferences, Mat &nearestBlock, int channelsNumber)
{
    int currentSum;
    Mat possibleBlock;

    for (int i = startRow; i <= endRow; i++) {
        for (int j = startCol; j <= endCol; j++) {
            possibleBlock = Mat(previousFrame, Rect(j, i, this->blockSize, this->blockSize));

            if (channelsNumber == 1) {
                subtract(currentBlock, possibleBlock, blocksDifferences, noArray(), CV_16SC1);
            } else if (channelsNumber == 3) {
                subtract(currentBlock, possibleBlock, blocksDifferences, noArray(), CV_16SC3);
            }

            currentSum = sum(sum(abs(blocksDifferences)))[0];

            if (currentSum < lastSum)
            {
                d_x = j;
                d_y = i;
                blocksDifferences.copyTo(nearestBlock);
                lastSum = currentSum;
                // If the difference between blocks is 0, no need to keep searching.
                if (lastSum < 1000) {
                    break;
                }
            }
        }
        // If the difference between blocks is 0, no need to keep searching.
        if (lastSum < 1000) {
            break;
        }
    }
}

InterDecoder::InterDecoder(class GolombDecoder &GolombDecoder, int blockSize, int searchArea, int shift) : GolombDecoder(GolombDecoder), blockSize(blockSize), searchArea(searchArea), shift(shift)
{
}

InterDecoder::~InterDecoder()
{
}

void InterDecoder::decode(Mat &previousFrame, Mat &currentFrame)
{
    int max_x = currentFrame.cols - this->blockSize;
    int max_y = currentFrame.rows - this->blockSize;
    int d_x;
    int d_y;
    int error;

    GolombDecoder.set_m(GolombDecoder.decode());

    for (int row = 0; row <= max_y; row += this->blockSize)
    {
        for (int col = 0; col <= max_x; col += this->blockSize)
        {
            d_x = GolombDecoder.decode();
            d_y = GolombDecoder.decode();
            for (int i = row; i < row + this->blockSize; i++) {
                for (int j = col; j < col + this->blockSize; j++) {
                    for (int channel = 0; channel < currentFrame.channels(); channel++)
                    {
                        error = GolombDecoder.decode();
                        if (error < 0) {
                            error = -1 * (abs(error) >> this->shift);
                        } else {
                            error >>= this->shift;
                        }
                        currentFrame.ptr<uchar>(i, j)[channel] = previousFrame.ptr<uchar>(d_y + i - row, d_x + j - col)[channel] + error;
                    }
                }
            }
        }
    }
}