#include <opencv2/opencv.hpp>
#include <iostream>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

using namespace std;
using namespace cv;

int thresholdType = 3;
int thresholdValue = 0;
const int maxBinaryValue = 255;
const int maxThresholdType = 4;
const int maxThresholdValue = 255;

const char* windowName = "Thresholding";

static void Threshold_Demo(int, void* userData) {
    Mat frame = *(Mat*)userData;
    Mat thresholdedImage;
    threshold(frame, thresholdedImage, thresholdValue, maxBinaryValue, thresholdType);
    imshow(windowName, thresholdedImage);
}

static void onTrackbar(int, void* userData) {
    // Do nothing
}

int main() {
    VideoCapture video("../../vid/akiyo_qcif.y4m");

    if (!video.isOpened()) {
        cerr << "Failed to open video." << endl;
        return -1;
    }

    // Imprimir informações para o utilizador
    cout << "Selecione o tipo de threshold:\n";
    cout << "0: Binary\n1: Binary Inverted\n2: Threshold Truncated\n";
    cout << "3: Threshold to Zero\n4: Threshold to Zero Inverted\n";
    


    Mat frame;
    namedWindow(windowName, WINDOW_AUTOSIZE);
    
    createTrackbar("Type", windowName, &thresholdType, maxThresholdType, onTrackbar);
    createTrackbar("Value", windowName, &thresholdValue, maxThresholdValue, onTrackbar);

    while (true) {
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, frame, Size(500, 500));

        // imshow("Original", frame);

        thresholdType = getTrackbarPos("Type", windowName);
        thresholdValue = getTrackbarPos("Value", windowName);

        Threshold_Demo(0, &frame);

        // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}