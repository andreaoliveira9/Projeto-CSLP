#include "PredictiveCoding.hpp"

void PredictiveCoding::encodeAndPredict(Mat frame, int m, BitStream *bs) {
    Golomb golombEncoder(bs, m);
    vector<Mat> rgbChannels(3);
    split(frame, rgbChannels);

    int prevA, prevB, prevC, error, predictedValue;
    for (int channel = 0; channel < 3; channel++) {
        Mat channelFrame = rgbChannels[channel];
        Mat predictedFrame = Mat::zeros(Size(channelFrame.cols, channelFrame.rows), CV_8UC1);

        for (int row = 0; row < channelFrame.rows; row++) {
            for (int col = 0; col <= channelFrame.cols; col++) {
                int a, b, c;

                if (row == 0 && col == 0) {
                    a = 0;
                    b = 0;
                    c = 0;
                } else if (row == 0 && col > 0) {
                    a = static_cast<int>(channelFrame.at<u_char>(row, col - 1));
                    b = 0;
                    c = 0;
                } else if (col == 0 && row > 0) {
                    a = 0;
                    b = 0;
                    c = static_cast<int>(channelFrame.at<u_char>(row - 1, col));
                } else {
                    a = static_cast<int>(channelFrame.at<u_char>(row, col - 1));
                    b = static_cast<int>(channelFrame.at<u_char>(row - 1, col));
                    c = static_cast<int>(channelFrame.at<u_char>(row - 1, col - 1));
                }

                if (c <= min(a, b)) {
                    predictedValue = max(a, b);
                } else if (c >= max(a, b)) {
                    predictedValue = min(a, b);
                } else {
                    predictedValue = a + b - c;
                }

                error = static_cast<int>(channelFrame.at<u_char>(row, col)) - predictedValue;
                predictedFrame.at<u_char>(row, col) = static_cast<u_char>(predictedValue);

                golombEncoder.encode(error);
                golombEncoder.encode(predictedValue);
            }
        }
    }
}

int PredictiveCoding::decodeAndReconstruct(BitStream *bs, int m, int rows, int cols) {
    Golomb golombDecoder(bs, m);
    vector<Mat> channels;
    int error, pixelValue;

    if (rows == 0 || cols == 0) {
        return -1;
    }

    for (int channel = 0; channel < 3; channel++) {
        Mat channelFrame = Mat::zeros(rows, cols, CV_8UC1);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col <= cols; col++) {
                error = golombDecoder.decode();
                pixelValue = golombDecoder.decode();
                pixelValue += error;
                channelFrame.at<u_char>(row, col) = static_cast<u_char>(pixelValue);
            }
        }

        channels.push_back(channelFrame);
    }

    Mat reconstructedImage;
    merge(channels, reconstructedImage);
    imshow("Reconstructed Image", reconstructedImage);
    char key = static_cast<char>(waitKey(3));

    return 0;
}