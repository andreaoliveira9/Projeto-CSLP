#include "BitStream.cpp"    
#include "Golomb.cpp"
#include "intraCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    intraCoding intraDecoder;
    BitStream bitStreamDecoder("encoded_image.bin", "read");
    int m = bitStreamDecoder.readNBits(5);
    int imageHeight = bitStreamDecoder.readNBits(12);
    int imageWidth = bitStreamDecoder.readNBits(12);
    int frameCount = bitStreamDecoder.readNBits(32);

    while (frameCount--) {
        Mat result = intraDecoder.decodeAndReconstruct(&bitStreamDecoder, m, imageHeight, imageWidth);
        if (frameCount == -1) {
            break;
        }
    }
}
