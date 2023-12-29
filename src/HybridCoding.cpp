#include "HybridCoding.hpp"

HybridEncoder::HybridEncoder(string inputFile, int periodicity, int searchArea, int shift) : periodicity(periodicity), searchArea(searchArea), shift(shift) {
    // read file header
    ifstream file(inputFile, ios::binary);

    // Read the file header

    string fileHeader;
    getline(file, fileHeader);

    // split the file header into tokens

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

    // open the video file
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

    IntraEncoder intraEncoder(GolombEncoder, shift);
    InterEncoder interEncoder(GolombEncoder, blockSize, searchArea, shift);

    Mat currentFrame;
    Mat previousFrame;

    GolombEncoder.encode(format);
    GolombEncoder.encode(searchArea);
    GolombEncoder.encode(shift);
    GolombEncoder.encode(periodicity);
    GolombEncoder.encode(frameNumber);

    int count = 0;
    switch (format) {
        case 0: 
        {
            while (true) {
                video >> currentFrame;
                if (currentFrame.empty()) {
                    break;
                };
                currentFrame = converter.rgb_to_yuv444(currentFrame);

                if (count == 0) {
                    int a = currentFrame.cols;
                    int b = currentFrame.rows;
                    if (a != b) {
                        int gcd = -1;
                        while (b != 0)
                        {
                            a %= b;
                            if (a == 0)
                                gcd = b;
                            break;
                            b %= a;
                        }
                        if (gcd == -1)
                            gcd = a;
                        if (gcd == a || gcd == b)
                            gcd = 16;
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

                if (count % periodicity == 0) {
                    currentFrame.copyTo(previousFrame);
                    intraEncoder.encode(currentFrame);
                } else {
                    interEncoder.encode(previousFrame, currentFrame);
                }
                count++;
            }
            break;
        }
        case 1: 
        {
            while (true) {
                video >> currentFrame;
                if (currentFrame.empty()) {
                    break;
                };
                currentFrame = converter.rgb_to_yuv422(currentFrame);

                if (count == 0) {
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

                if (count % periodicity == 0) {
                    currentFrame.copyTo(previousFrame);
                    intraEncoder.encode(currentFrame);
                } else {
                    interEncoder.encode(previousFrame, currentFrame);
                }
                count++;
            }
            break;
        }
        case 2:
        {
            while (true) {
                video >> currentFrame;
                if (currentFrame.empty()) {
                    break;
                };
                currentFrame = converter.rgb_to_yuv420(currentFrame);

                if (count == 0) {
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

                if (count % periodicity == 0) {
                    currentFrame.copyTo(previousFrame);
                    intraEncoder.encode(currentFrame);
                } else {
                    interEncoder.encode(previousFrame, currentFrame);
                }
                count++;
            }
            break;
        }
    }

    GolombEncoder.finishEncoding();
};

HybridDecoder::HybridDecoder(string inputFile) {
    this->inputFile = inputFile;
};

HybridDecoder::~HybridDecoder() {};

void HybridDecoder::decode(string outputFile) {
    Converter converter;
    GolombDecoder GolombDecoder(this->inputFile);

    int format = GolombDecoder.decode();
    int searchArea = GolombDecoder.decode();
    int shift = GolombDecoder.decode();
    int periodicity = GolombDecoder.decode();
    int frameNumber = GolombDecoder.decode();
    int blockSize = GolombDecoder.decode();
    int width = GolombDecoder.decode();
    int height = GolombDecoder.decode();

    IntraDecoder intraDecoder(GolombDecoder, shift);
    InterDecoder interDecoder(GolombDecoder, blockSize, searchArea, shift);

    Mat currentFrame;
    Mat previousFrame;

    int count = 0;
    switch (format) {
        case 0:
        {
            while (count < frameNumber) {
                currentFrame = Mat::zeros(height, width, CV_8UC3);

                if (count % periodicity == 0) {
                    intraDecoder.decode(currentFrame);
                    currentFrame.copyTo(previousFrame);
                } else {
                    interDecoder.decode(previousFrame, currentFrame);
                }

                imshow("Image", converter.yuv444_to_rgb(currentFrame));
                if (waitKey(10) == 27) {
                    destroyAllWindows();
                }; 
                count++;
            }
        }
        case 1:
        {
            while (count < frameNumber) {
                currentFrame = Mat::zeros(height, width, CV_8UC1);

                if (count % periodicity == 0) {
                    intraDecoder.decode(currentFrame);
                    currentFrame.copyTo(previousFrame);
                } else {
                    interDecoder.decode(previousFrame, currentFrame);
                }

                imshow("Image", converter.yuv422_to_rgb(currentFrame));
                if (waitKey(10) == 27) {
                    destroyAllWindows();
                }; 
                count++;
            }
        }
        case 2:
        {
            while (count < frameNumber) {
                currentFrame = Mat::zeros(height, width, CV_8UC1);

                if (count % periodicity == 0) {
                    intraDecoder.decode(currentFrame);
                    currentFrame.copyTo(previousFrame);
                } else {
                    interDecoder.decode(previousFrame, currentFrame);
                }

                imshow("Image", converter.yuv420_to_rgb(currentFrame));
                if (waitKey(10) == 27) {
                    destroyAllWindows();
                }; 
                count++;
            }
        }
    }
};
