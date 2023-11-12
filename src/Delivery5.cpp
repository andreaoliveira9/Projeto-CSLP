#include "BitStream.cpp"
#include "Golomb.cpp"
#include "PredictiveCoding.cpp"
#include "HybridCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    string outputFileName = "encoded_image.bin";  
    /* BitStream bitStreamEncoder(outputFileName, "write"); */
    

    VideoCapture videoCapture("../../vid/akiyo_qcif.y4m");
    if (!videoCapture.isOpened()) {
        cout << "Erro ao abrir o vídeo" << endl;
        return 0;
    }

    int m = 24;
    int blockSize = 8; 
    int searchArea= 3;
    int periodicity = 3;
    int frameWidth = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    int frameCountTotal = videoCapture.get(CAP_PROP_FRAME_COUNT);

    /* bitStreamEncoder.writeNBits(m, 5);
    bitStreamEncoder.writeNBits(frameHeight, 12);
    bitStreamEncoder.writeNBits(frameWidth, 12);
    bitStreamEncoder.writeNBits(frameCountTotal, 9);
    bitStreamEncoder.writeNBits(blockSize, 4);
    bitStreamEncoder.writeNBits(searchArea, 4);
    bitStreamEncoder.writeNBits(periodicity, 4);

    HybridCoding hybridEncoder(&bitStreamEncoder, blockSize, searchArea, periodicity, m); */

    Mat previousFrame;
    int frameCount = 0;
    /* while (true) {
        Mat currentFrame;
        videoCapture >> currentFrame;

        if (currentFrame.empty()) {
            break;
        }

        hybridEncoder.encode(previousFrame, currentFrame, frameCount);

        previousFrame = currentFrame;
        frameCount++;
    }

    bitStreamEncoder.close(); */

    BitStream bitStreamDecoder(outputFileName, "read");
    m = bitStreamDecoder.readNBits(5);
    frameHeight = bitStreamDecoder.readNBits(12);
    frameWidth = bitStreamDecoder.readNBits(12);
    frameCountTotal = bitStreamDecoder.readNBits(9);
    blockSize = bitStreamDecoder.readNBits(4);
    searchArea = bitStreamDecoder.readNBits(4);
    periodicity = bitStreamDecoder.readNBits(4);
    HybridCoding hybridDecoder(&bitStreamDecoder, blockSize, searchArea, periodicity, m);

    frameCount = 0;
    while (frameCountTotal--) {
        Mat frame = hybridDecoder.decode(previousFrame, frameHeight, frameWidth, frameCount);
        
        previousFrame = frame;
        frameCount++;
    }
    videoCapture.release();
}