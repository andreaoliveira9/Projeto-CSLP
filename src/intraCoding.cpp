#include "intraCoding.hpp"
#include <unistd.h>

IntraEncoder::IntraEncoder(GolombEncoder &golombEncoder, int shift) : golombEncoder(golombEncoder), shift(shift)
{
}

IntraEncoder::~IntraEncoder()
{
}

void IntraEncoder::encode(Mat &currentFrame) {
    int a;
    int b;
    int c;
    int error;
    int predictedValue;
    int mGolombParameter;
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

    
    for (int row = 1; row < frame.rows; row++) {
        for (int col = 1; col < frame.cols; col++) {
            for (int channel = 0; channel < channelsNumber; channel++) {
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
                
                error < 0 ? error = -1 * (abs(error) >> this->shift) : error >>= this->shift;

                errorMatrix.ptr<short>(row - 1, col - 1)[channel] = error;

                error < 0 ? error = -1 * (abs(error) << this->shift) : error <<= this->shift;

                frame.ptr<uchar>(row, col)[channel] = (unsigned char)predictedValue + error;
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

IntraDecoder::IntraDecoder(GolombDecoder &golombDecoder, int shift) : golombDecoder(golombDecoder), shift(shift)
{
}

IntraDecoder::~IntraDecoder()
{
}

void IntraDecoder::decode(Mat &currentFrame) {
    int a;
    int b;
    int c;
    int error;
    int predictedValue;

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

                error = golombDecoder.decode();                

                error < 0 ? error = -1 * (abs(error) << this->shift) : error <<= this->shift;

                if (c <= min(a, b)) {
                    predictedValue = max(a, b);
                } else if (c >= max(a, b)) {
                    predictedValue = min(a, b);
                } else {
                    predictedValue = a + b - c;
                }

                currentFrame.ptr<uchar>(row, col)[channel] = (unsigned char)predictedValue + error;
            }
        }
    }

    currentFrame = currentFrame(Rect(1, 1, currentFrame.cols - 1, currentFrame.rows - 1));
}