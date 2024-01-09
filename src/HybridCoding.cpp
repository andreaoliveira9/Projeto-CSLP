#include "HybridCoding.hpp"
#include <chrono>
#include <iostream>

HybridEncoder::HybridEncoder(string inputFile, int periodicity, int searchArea, int quantization1, int quantization2, int quantization3): periodicity(periodicity), searchArea(searchArea), quantization1(quantization1), quantization2(quantization2), quantization3(quantization3) {
    ifstream file(inputFile, ios::binary);

    string fileHeader;
    getline(file, fileHeader);

    istringstream iss(fileHeader);

    vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};

    if (tokens.size() > 6) {
        if (tokens[6].compare("C444") == 0) {
            format = 0;
        } else if (tokens[6].compare("C422") == 0) {
            format = 1;
        }
    } else {
        format = 2;
    }

    video = VideoCapture(inputFile);

    videoWidth = video.get(CAP_PROP_FRAME_WIDTH);
    videoHeight = video.get(CAP_PROP_FRAME_HEIGHT);
    frameNumber = video.get(CAP_PROP_FRAME_COUNT);
};

HybridEncoder::~HybridEncoder() {
};


void HybridEncoder::encode(string outputFile) {
    Converter converter;
    GolombEncoder GolombEncoder(outputFile);

    IntraEncoder intraEncoder(GolombEncoder, quantization1, quantization2, quantization3);
    InterEncoder interEncoder(GolombEncoder, blockSize, searchArea, quantization1, quantization2, quantization3);

    Mat currentFrame;
    Mat previousFrame;

    GolombEncoder.encode(format);
    GolombEncoder.encode(searchArea);
    GolombEncoder.encode(frameNumber);

    int count = 0;
    while (true) {
        video >> currentFrame;
        if (currentFrame.empty()) {
            break;
        };

        switch(format) {
            case 0:
            {
                currentFrame = converter.rgb_to_yuv444(currentFrame);
                break;
            }
            case 1:
            {
                currentFrame = converter.rgb_to_yuv422(currentFrame);
                break;
            }
            case 2:
            {
                currentFrame = converter.rgb_to_yuv420(currentFrame);
                break;
            }
        }

        if (count == 0) {
            setBestBlockSize(currentFrame, GolombEncoder, interEncoder);
        }

        if (count % periodicity == 0) {
            GolombEncoder.encode(0);
            currentFrame.copyTo(previousFrame);
            intraEncoder.encode(currentFrame);
        } else {
            GolombEncoder.encode(1);
            interEncoder.encode(previousFrame, currentFrame);
        }
        count++;
    }

    GolombEncoder.finishEncoding();
};

void HybridEncoder::setBestBlockSize(Mat &currentFrame, GolombEncoder &GolombEncoder, InterEncoder &interEncoder) {
    int a = currentFrame.cols;
    int b = currentFrame.rows;
    if (a != b) {
        int gcd = -1;
        while (b != 0) {
            a %= b;
            if (a == 0) {
                gcd = b;
            }
            break;
            b %= a;
        }
        if (gcd == -1) {
            gcd = a;
        }
        if (gcd == a || gcd == b) {
            gcd = 16;
        }
        this->blockSize = gcd;
        interEncoder.setBlockSize(gcd);
        GolombEncoder.encode(gcd);
    } else {
        this->blockSize = 16;
        interEncoder.setBlockSize(16);
        GolombEncoder.encode(16);
    }

    GolombEncoder.encode(currentFrame.cols);
    GolombEncoder.encode(currentFrame.rows);
}

HybridDecoder::HybridDecoder(string inputFile) {
    this->inputFile = inputFile;
};

HybridDecoder::~HybridDecoder() {};

void HybridDecoder::decode(string outputFile) {
    Converter converter;
    GolombDecoder GolombDecoder(this->inputFile);

    int format = GolombDecoder.decode();
    int searchArea = GolombDecoder.decode();
    int frameNumber = GolombDecoder.decode();
    int blockSize = GolombDecoder.decode();
    int width = GolombDecoder.decode();
    int height = GolombDecoder.decode();

    IntraDecoder intraDecoder(GolombDecoder);
    InterDecoder interDecoder(GolombDecoder, blockSize, searchArea);

    Mat currentFrame;
    Mat previousFrame;

    int count = 0;
    while (count < frameNumber) {
        switch (format) {
            case 0:
            {
                currentFrame = Mat::zeros(height, width, CV_8UC3);
                break;
            }
            case 1:
            {
                currentFrame = Mat::zeros(height, width, CV_8UC1);
                break;
            }
            case 2:
            {
                currentFrame = Mat::zeros(height, width, CV_8UC1);
                break;
            }
        }
        

        if (GolombDecoder.decode() == 0) {
            intraDecoder.decode(currentFrame);
            currentFrame.copyTo(previousFrame);
        } else {
            interDecoder.decode(previousFrame, currentFrame);
        }

        switch (format) {
            case 0:
            {
                imshow("Image", converter.yuv444_to_rgb(currentFrame));
                break;
            }
            case 1:
            {
                imshow("Image", converter.yuv422_to_rgb(currentFrame));
                break;
            }
            case 2:
            {
                imshow("Image", converter.yuv420_to_rgb(currentFrame));
                break;
            }
        }

        if (waitKey(10) == 27) {
            destroyAllWindows();
        }; 
        count++;
    }
};
