#include <opencv2/opencv.hpp>
#include <iostream>

#include "PredictiveCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    string outputFileName = "encoded_image.bin";
    BitStream bitStreamEncoder(outputFileName, "write");
    int golombParameter = 24;
    PredictiveCoding predictorEncoder;

    VideoCapture videoCapture("../../vid/akiyo_qcif.y4m");
    if (!videoCapture.isOpened()) {
        cout << "Erro ao abrir o vídeo" << endl;
        return 0;
    }

    int frameWidth = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    int frameCount = videoCapture.get(CAP_PROP_FRAME_COUNT);

    bitStreamEncoder.writeNBits(golombParameter, 5);
    bitStreamEncoder.writeNBits(frameHeight, 12);
    bitStreamEncoder.writeNBits(frameWidth, 12);

    while (true) {
        Mat currentFrame;
        videoCapture >> currentFrame;
        if (currentFrame.empty()) {
            break;
        }
        predictorEncoder.encodeAndPredict(currentFrame, golombParameter, &bitStreamEncoder);
    }

    bitStreamEncoder.close();

    PredictiveCoding predictorDecoder;
    BitStream bitStreamDecoder(outputFileName, "read");
    golombParameter = bitStreamDecoder.readNBits(5);
    int imageHeight = bitStreamDecoder.readNBits(12);
    int imageWidth = bitStreamDecoder.readNBits(12);

    while (frameCount--) {
        int result = predictorDecoder.decodeAndReconstruct(&bitStreamDecoder, golombParameter, imageHeight, imageWidth);
        if (result == -1) {
            break;
        }
    }

    videoCapture.release();
}
