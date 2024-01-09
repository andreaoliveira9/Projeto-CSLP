#include "interCoding.hpp"

InterEncoder::InterEncoder(class GolombEncoder &GolombEncoder, int blockSize, int searchArea, int quantization1, int quantization2, int quantization3): GolombEncoder(GolombEncoder), blockSize(blockSize), searchArea(searchArea), quantization1(quantization1), quantization2(quantization2), quantization3(quantization3)
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
    int d_x;
    int d_y;
    int startCol;
    int startRow;
    int endCol;
    int endRow;
    Mat blocksDifferences;
    Mat fewestDifferences;
    Mat auxiliarFrame;
    Mat currentBlock;

    int count = 0;
    int max_x = currentFrame.cols - this->blockSize;
    int max_y = currentFrame.rows - this->blockSize;
    int channelsNumber = currentFrame.channels();
    queue<int> vectorCoordinates;

    if (channelsNumber == 3) {
        blocksDifferences = Mat::zeros(this->blockSize, this->blockSize, CV_16SC3);
        auxiliarFrame = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC3);
    } else if (channelsNumber == 1) {
        blocksDifferences = Mat::zeros(this->blockSize, this->blockSize, CV_16SC1);
        auxiliarFrame = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC1);
    }

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

            findNearestBlock(previousFrame, currentBlock, startRow, startCol, endRow, endCol, d_x, d_y, lastSum, blocksDifferences, fewestDifferences, channelsNumber);
            
            vectorCoordinates.push(d_x);
            vectorCoordinates.push(d_y);

            Rect rect(col, row, this->blockSize, this->blockSize);
            fewestDifferences.copyTo(auxiliarFrame(rect));
        }
    }

    mGolombParameter = GolombEncoder.optimal_m(auxiliarFrame);

    if (GolombEncoder.get_m() == mGolombParameter) {
        GolombEncoder.encode(0);
    } else {
        GolombEncoder.encode(mGolombParameter);
        GolombEncoder.set_m(mGolombParameter);
    }

    count = 0;

    for (int row = 0; row <= max_y; row += this->blockSize) {
        for (int col = 0; col <= max_x; col += this->blockSize) {
            encodeAndApplyMotionCompenstation(previousFrame, currentFrame, auxiliarFrame, row, col, channelsNumber, vectorCoordinates);
        }
    }
}

void InterEncoder::findNearestBlock(Mat &previousFrame, Mat &currentBlock, int startRow, int startCol, int endRow, int endCol, int &d_x, int &d_y, int &lastSum, Mat &blocksDifferences, Mat &fewestDifferences, int channelsNumber)
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
                blocksDifferences.copyTo(fewestDifferences);
                lastSum = currentSum;

                if (lastSum < 1000) {
                    break;
                }
            }
        }

        if (lastSum < 1000) {
            break;
        }
    }
}

void InterEncoder::encodeAndApplyMotionCompenstation(Mat &previousFrame, Mat &currentFrame, Mat &auxiliarFrame, int row, int col, int channelsNumber, queue<int> &vectorCoordinates) {
    int error;
    int d_x = vectorCoordinates.front();
    vectorCoordinates.pop();
    int d_y = vectorCoordinates.front();
    vectorCoordinates.pop();
    GolombEncoder.encode(d_x);
    GolombEncoder.encode(d_y);

    for (int i = row; i < row + this->blockSize; i++) {
        for (int j = col; j < col + this->blockSize; j++) {
            for (int channel = 0; channel < channelsNumber; channel++) {
                error = auxiliarFrame.ptr<short>(i, j)[channel];

                int quantizationLevel = (channel == 0) ? quantization1 : ((channel == 1) ? quantization2 : quantization3);

                int steps = 256 / quantizationLevel;
                int quantizedError = floor(error/steps) * steps;

                currentFrame.ptr<uchar>(i, j)[channel] = quantizedError + previousFrame.ptr<uchar>(i, j)[channel];

                GolombEncoder.encode(quantizedError);
            }
        }
    }
}

InterDecoder::InterDecoder(class GolombDecoder &GolombDecoder, int blockSize, int searchArea) : GolombDecoder(GolombDecoder), blockSize(blockSize), searchArea(searchArea)
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
    int quantizedError;

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
                        quantizedError = GolombDecoder.decode();

                        currentFrame.ptr<uchar>(i, j)[channel] = previousFrame.ptr<uchar>(d_y + i - row, d_x + j - col)[channel] + quantizedError;
                    }
                }
            }
        }
    }
}