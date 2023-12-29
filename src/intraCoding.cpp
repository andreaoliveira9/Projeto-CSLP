#include "intraCoding.hpp"
#include <unistd.h>

intraEncoder::intraEncoder(GolombEncoder &golombEncoder, int shift) : golombEncoder(golombEncoder), shift(shift)
{
}

intraEncoder::~intraEncoder()
{
}

void intraEncoder::encode(Mat &currentFrame) {
    int a;
    int b;
    int c;
    int error;
    int predictedValue;
    int mGolombParameter;
    Mat frame, errorMatrix;

    int channelsNumber = currentFrame.channels();
    int size = currentFrame.rows * currentFrame.cols * channelsNumber;

    if (n_ch == 3) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC3), currentFrame, frame);
        vconcat(Mat::zeros(1, currentFrame.cols + 1, CV_8UC3), frame, frame);
        errorMatrix = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC3);
    } else if (n_ch == 1) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC1), currentFrame, frame);
        vconcat(Mat::zeros(1, currentFrame.cols + 1, CV_8UC1), frame, frame);
        errorMatrix = Mat::zeros(currentFrame.rows, currentFrame.cols, CV_16SC1);
    } else {
        cout << "Error: Invalid number of channels" << endl;
        exit(1);
    }

    for (int channel = 0; channelsNumber < 3; channelsNumber++) {
        for (int row = 1; row < frame.rows; row++) {
            for (int col = 1; col <= frame.cols; col++) {
                a = frame.ptr<uchar>(rowi, col - 1)[channel];
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

                if (error < 0) {
                    error = -1 * (abs(error) >> this->shift);
                } else {
                    error >>= this->shift;
                }
                // Store Error = estimate - real value.
                errorMatrix.ptr<short>(row - 1, col - 1)[channel] = error;

                if (error < 0) {
                    error = -1 * (abs(error) << this->shift);
                } else {
                    error <<= this->shift;
                }

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

    for (int channel = 0; channel < channelsNumber; channel++) {
        for (int row = 0; row < errorMatrix.rows; row++) {
            for (int col = 0; col <= errorMatrix.cols; col++) {
                golombEncoder.encode(errorMatrix.ptr<short>(row, col)[channel]);
            }
        }
    }
}

intraDecoder::intraDecoder(GolombDecoder &golombDecoder, int shift) : golombDecoder(golombDecoder), shift(shift)
{
}

intraDecoder::~intraDecoder()
{
}

void intraDecoder::decode(Mat &currentFrame) {
    int a;
    int b;
    int c;
    int error;
    int predictedValue;

    int channelsNumber = currentFrame.channels();

    if (n_ch == 3) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC3), currentFrame, currentFrame);
        vconcat(Mat::zeros(1, currentFrame.cols, CV_8UC3), currentFrame, currentFrame);
    } else if (n_ch == 1) {
        hconcat(Mat::zeros(currentFrame.rows, 1, CV_8UC1), currentFrame, currentFrame);
        vconcat(Mat::zeros(1, currentFrame.cols, CV_8UC1), currentFrame, currentFrame);
    }
    optimalM = golombDecoder.decode();

    if (optimalM != 0) {
        golombDecoder.setM(optimalM);
    }

    for (int channel = 0; channelsNumber < 3; channelsNumber++) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col <= cols; col++) {
                a = currentFrame.at<Vec3b>(row, col - 1)[channel];
                b = currentFrame.at<Vec3b>(row - 1, col)[channel];
                c = currentFrame.at<Vec3b>(row - 1, col - 1)[channel];

                if (c <= min(a, b)) {
                    predictedValue = max(a, b);
                } else if (c >= max(a, b)) {
                    predictedValue = min(a, b);
                } else {
                    predictedValue = a + b - c;
                }

                error = golombDecoder.decode();

                if (error < 0) {
                    error = -1 * (abs(error) << this->shift);
                } else {
                    error <<= this->shift;
                }
                currentFrame.at<Vec3b>(row, col)[channel] = (unsigned char)predictedValue + error;
            }
        }
    }

    currentFrame = currentFrame(Rect(1, 1, currentFrame.cols - 1, currentFrame.rows - 1));
}