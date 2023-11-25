#include "BitStream.cpp"
#include "Golomb.cpp"
#include "PredictiveCoding.cpp"
#include "HybridCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
    BitStream bitStreamDecoder("encoded_image.bin", "read");
    int m = bitStreamDecoder.readNBits(5);
    int frameHeight = bitStreamDecoder.readNBits(12);
    int frameWidth = bitStreamDecoder.readNBits(12);
    int blockSize = bitStreamDecoder.readNBits(4);
    int searchArea = bitStreamDecoder.readNBits(4);
    int frameCount = bitStreamDecoder.readNBits(32);
    HybridCoding hybridDecoder(&bitStreamDecoder, blockSize, searchArea, m);

    Mat previousFrame;
    while (frameCount--) {
        Mat frame = hybridDecoder.decode(previousFrame, frameHeight, frameWidth);
        previousFrame = frame;
    }
}
