#include "intraCoding.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

IntraEncoder::IntraEncoder(GolombEncoder &golombEncoder)
    : golombEncoder(golombEncoder)
{
}

IntraEncoder::~IntraEncoder()
{
}

void IntraEncoder::encode(Mat &currentFrame, int quantization1, int quantization2, int quantization3, int &totalSignal, int &totalNoise)

{
    int a;
    int b;
    int c;
    int error;
    int predictedValue;
    int mGolombParameter;
    int quantizationLevel;
    int steps;
    int quantizedError;
    Mat frame, errorMatrix;

    int channelsNumber = currentFrame.channels();

    if (channelsNumber == 3) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC3), currentFrame, frame);
        vconcat(Mat::zeros(1, currentFrame.cols + 1, CV_8UC3), frame, frame);
        errorMatrix = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC3);
    } else if (channelsNumber == 1) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC1), currentFrame, frame);
        vconcat(Mat::zeros(1, currentFrame.cols + 1, CV_8UC1), frame, frame);
        errorMatrix = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC1);
    } else {
        cout << "Error: Invalid number of channels" << endl;
        exit(1);
    }

    for (int row = 1; row < frame.rows; row++)
    {
        for (int col = 1; col < frame.cols; col++)
        {
            for (int channel = 0; channel < channelsNumber; channel++)
            {
                a = frame.ptr<uchar>(row, col - 1)[channel];
                b = frame.ptr<uchar>(row - 1, col)[channel];
                c = frame.ptr<uchar>(row - 1, col - 1)[channel];

                if (c <= min(a, b)) {
                    predictedValue = max(a, b);
                } else if (c >= max(a, b)) {
                    predictedValue = min(a, b);
                } else {
                    predictedValue = a + b - c;
                }

                error = frame.ptr<uchar>(row, col)[channel] - predictedValue;

                if (quantization1 == 255 && quantization2 == 255 && quantization3 == 255) {
                    errorMatrix.ptr<short>(row - 1, col - 1)[channel] = error;

                    frame.ptr<uchar>(row, col)[channel] = (unsigned char)predictedValue + error;
                } else {
                    quantizationLevel = (channel == 0) ? quantization1 : ((channel == 1) ? quantization2 : quantization3);

                    steps = 256 / quantizationLevel;
                    quantizedError = floor(error/steps) * steps;

                    errorMatrix.ptr<short>(row - 1, col - 1)[channel] = quantizedError;

                    frame.ptr<uchar>(row, col)[channel] = (unsigned char)predictedValue + quantizedError;
                }

                totalSignal += abs(error);
                totalNoise += abs(error - quantizedError);
            }
        }
    }

    mGolombParameter = golombEncoder.optimal_m(errorMatrix);
    if (golombEncoder.get_m() == mGolombParameter) {
        golombEncoder.encode(0);
    } else {
        golombEncoder.encode(mGolombParameter);
        golombEncoder.set_m(mGolombParameter);
    }

    for (int row = 0; row < errorMatrix.rows; row++) {
        for (int col = 0; col < errorMatrix.cols; col++) {
            for (int channel = 0; channel < channelsNumber; channel++) {
                golombEncoder.encode(errorMatrix.ptr<short>(row, col)[channel]);
            }
        }
    }
}

IntraDecoder::IntraDecoder(GolombDecoder &golombDecoder)
    : golombDecoder(golombDecoder)
{
}

IntraDecoder::~IntraDecoder()
{
}

void IntraDecoder::decode(Mat &currentFrame)
{
    int a;
    int b;
    int c;
    int error;
    int predictedValue;
    int quantizedError;

    int channelsNumber = currentFrame.channels();

    if (channelsNumber == 3) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC3), currentFrame, currentFrame);
        vconcat(Mat::zeros(1, currentFrame.cols, CV_8UC3), currentFrame, currentFrame);
    } else if (channelsNumber == 1) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC1), currentFrame, currentFrame);
        vconcat(Mat::zeros(1, currentFrame.cols, CV_8UC1), currentFrame, currentFrame);
    }
    int optimalM = golombDecoder.decode();

    if (optimalM != 0) {
        golombDecoder.set_m(optimalM);
    }

    for (int row = 1; row < currentFrame.rows; row++) {
        for (int col = 1; col < currentFrame.cols; col++) {
            for (int channel = 0; channel < channelsNumber; channel++) {
                a = currentFrame.ptr<uchar>(row, col - 1)[channel];
                b = currentFrame.ptr<uchar>(row - 1, col)[channel];
                c = currentFrame.ptr<uchar>(row - 1, col - 1)[channel];

                if (c <= min(a, b)) {
                    predictedValue = max(a, b);
                } else if (c >= max(a, b)) {
                    predictedValue = min(a, b);
                } else {
                    predictedValue = a + b - c;
                }

                quantizedError = golombDecoder.decode();

                currentFrame.ptr<uchar>(row, col)[channel] = (unsigned char)predictedValue + quantizedError;
            }
        }
    }

    currentFrame = currentFrame(Rect(1, 1, currentFrame.cols - 1, currentFrame.rows - 1));
}
