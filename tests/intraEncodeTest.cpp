#include "BitStream.cpp"    
#include "Golomb.cpp"
#include "intraCoding.cpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]){
    BitStream bitStreamEncoder("encoded_image.bin", "write");
    intraCoding intraEncoder;
    
    VideoCapture videoCapture("../../vid/akiyo_qcif.y4m");
    if (!videoCapture.isOpened()) {
        cout << "Erro ao abrir o vídeo" << endl;
        return 0;
    }

    int m = 5;
    int frameWidth = videoCapture.get(CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(CAP_PROP_FRAME_HEIGHT);
    int frameCount = videoCapture.get(CAP_PROP_FRAME_COUNT);

    bitStreamEncoder.writeNBits(m, 5);
    bitStreamEncoder.writeNBits(frameHeight, 12);
    bitStreamEncoder.writeNBits(frameWidth, 12);
    bitStreamEncoder.writeNBits(frameCount, 32);

    while (true) {
        Mat currentFrame;
        videoCapture >> currentFrame;
        if (currentFrame.empty()) {
            break;
        }
        intraEncoder.encodeAndPredict(currentFrame, m, &bitStreamEncoder);
    }

    bitStreamEncoder.close();
    videoCapture.release();
}
