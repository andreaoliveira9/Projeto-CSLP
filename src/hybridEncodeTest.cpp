#include "BitStream.cpp"
#include "Golomb.cpp"
#include "PredictiveCoding.cpp"
#include "HybridCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    BitStream bitStreamEncoder("encoded_image.bin", "write");

    VideoCapture videoCapture("../../vid/akiyo_qcif.y4m");
    if (!videoCapture.isOpened()) {
        cout << "Erro ao abrir o vídeo" << endl;
        return 0;
    }

    int m = 5;
    int blockSize = 8; 
    int searchArea= 3;
    int periodicity = 3;
    int frameWidth = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    int frameCount = videoCapture.get(CAP_PROP_FRAME_COUNT);

    bitStreamEncoder.writeNBits(m, 5);
    bitStreamEncoder.writeNBits(frameHeight, 12);
    bitStreamEncoder.writeNBits(frameWidth, 12);
    bitStreamEncoder.writeNBits(blockSize, 4);
    bitStreamEncoder.writeNBits(searchArea, 4);
    bitStreamEncoder.writeNBits(frameCount, 32);
    HybridCoding hybridEncoder(&bitStreamEncoder, blockSize, searchArea, m, periodicity);

    Mat previousFrame;
    int frameCounter = 0;
    while (true) {
        cout << "Frame: " << frameCounter << endl;
        Mat currentFrame;
        videoCapture >> currentFrame;

        if (currentFrame.empty()) {
            break;
        }

        hybridEncoder.encode(previousFrame, currentFrame, frameCounter);

        previousFrame = currentFrame;
        frameCounter++;
    }

    bitStreamEncoder.close();

    videoCapture.release();
}
