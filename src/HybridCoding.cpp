#include "HybridCoding.hpp"
#include <chrono>
#include <iostream>

HybridEncoder::HybridEncoder(string inputFile, int periodicity, int searchArea, int quantization1, int quantization2, int quantization3): video(inputFile), periodicity(periodicity), searchArea(searchArea), quantization1(quantization1), quantization2(quantization2), quantization3(quantization3) {
    auto start_full = chrono::high_resolution_clock::now();
    this->frameNumber = video.get_n_frames();
    auto end_full = chrono::high_resolution_clock::now();
    double time_taken_full = chrono::duration_cast<chrono::nanoseconds>(end_full - start_full).count();
    time_taken_full *= 1e-9;

    this->timeToCreateReader = time_taken_full;
};

HybridEncoder::~HybridEncoder() {
};

double HybridEncoder::getTimeToCreateReader() {
    return this->timeToCreateReader; 
};

int HybridEncoder::getFrameNumber() {
    return this->frameNumber;
};

double HybridEncoder::getSignalToNoiseRatio() {
    return this->signalToNoiseRatio;
};

double HybridEncoder::getBitsPerPixel() {
    return this->bitsPerPixel;
};

void HybridEncoder::encode(string outputFile) {
    Converter converter;
    GolombEncoder GolombEncoder(outputFile);

    IntraEncoder intraEncoder(GolombEncoder);
    InterEncoder interEncoder(GolombEncoder, blockSize, searchArea);

    Mat currentFrame;
    Mat previousFrame;
    
    GolombEncoder.encode(searchArea);
    GolombEncoder.encode(frameNumber);

    int totalSignal = 0;
    int totalNoise = 0;

    int numberOfPixelsPerFrame = video.get_frame_size();
    int count = 0;
    while (video.nextFrame_exists()) {
        currentFrame = video.get_nextFrame();
        if (currentFrame.empty()) {
            break;
        };

        if (count == 0) {
            GolombEncoder.encode(currentFrame.cols);
            GolombEncoder.encode(currentFrame.rows);
            setBestBlockSize(currentFrame, GolombEncoder, interEncoder);
        }

        if (count % periodicity == 0) {
            GolombEncoder.encode(0);
            currentFrame.copyTo(previousFrame);
            intraEncoder.encode(currentFrame, quantization1, quantization2, quantization3, totalSignal, totalNoise);
        } else {
            GolombEncoder.encode(1);
            interEncoder.encode(previousFrame, currentFrame, quantization1, quantization2, quantization3, totalSignal, totalNoise);
        }
        count++;
    }

    this->signalToNoiseRatio = (double)totalSignal / (double)totalNoise;
    this->bitsPerPixel = GolombEncoder.getBitstreamSize() / ((double)numberOfPixelsPerFrame * frameNumber * 3);

    GolombEncoder.finishEncoding();
};

void HybridEncoder::setBestBlockSize(Mat &currentFrame, GolombEncoder &GolombEncoder, InterEncoder &interEncoder) {
    int cols = currentFrame.cols;
    int rows = currentFrame.rows;
    if (cols != rows) {
        int maxDivComum = -1;
        while (rows != 0) {
            cols %= rows;
            if (cols == 0) {
                maxDivComum = rows;
            }
            break;
            rows %= cols;
        }
        if (maxDivComum == -1) {
            maxDivComum = cols;
        }
        if (maxDivComum == cols || maxDivComum == rows) {
            maxDivComum = 16;
        }
        this->blockSize = maxDivComum;
        interEncoder.setBlockSize(maxDivComum);
        GolombEncoder.encode(maxDivComum);
    } else {
        this->blockSize = 16;
        interEncoder.setBlockSize(16);
        GolombEncoder.encode(16);
    }
}

HybridDecoder::HybridDecoder(string inputFile) {
    this->inputFile = inputFile;
};

HybridDecoder::~HybridDecoder() {};

void HybridDecoder::decode(string outputFile) {
    Converter converter;
    GolombDecoder GolombDecoder(this->inputFile);

    int searchArea = GolombDecoder.decode();
    int frameNumber = GolombDecoder.decode();
    int width = GolombDecoder.decode();
    int height = GolombDecoder.decode();
    int blockSize = GolombDecoder.decode();
    
    IntraDecoder intraDecoder(GolombDecoder);
    InterDecoder interDecoder(GolombDecoder, blockSize, searchArea);

    Mat currentFrame;
    Mat previousFrame;

    // Abra o arquivo Y4M para gravação
    std::ofstream y4mFile(outputFile, std::ios::binary);
    
    // Escreva o cabeçalho Y4M para YUV444
    y4mFile << "YUV4MPEG2 W" << width << " H" << height << " F30:1 Ip A0:0 C444" << std::endl;

    int count = 0;
    while (count < frameNumber) {
        currentFrame = Mat::zeros(height, width, CV_8UC3);

        if (GolombDecoder.decode() == 0) {
            intraDecoder.decode(currentFrame);
            currentFrame.copyTo(previousFrame);
        } else {
            interDecoder.decode(previousFrame, currentFrame);
        }

        // Escreva o frame atual no arquivo Y4M
        y4mFile.write(reinterpret_cast<const char*>(currentFrame.data), width * height * 3);

        imshow("Image", converter.yuv444_to_rgb(currentFrame));

        if (waitKey(10) == 27) {
            destroyAllWindows();
        }; 

        count++;
    }

    // Feche o arquivo Y4M
    y4mFile.close();
};