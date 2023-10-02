#include <iostream>
#include <vector>
#include "functions.cpp"

using namespace std;
using namespace cv;

int main() {
    VideoCapture video("../../vid/akiyo_qcif.y4m");

    if (!video.isOpened()) {
        cerr << "Failed to open video." << endl;
        return -1;
    }

    Mat frame, yuvFrame, rgbFrame;
    while (true) {
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, frame, Size(500, 500));

        // Convert RGB to YUV
        rgbToYuv(frame, yuvFrame);

        // Convert YUV back to RGB for display
        yuvToRgb(yuvFrame, rgbFrame);

        // Display the frames
        imshow("RGB", rgbFrame);
        imshow("YUV", yuvFrame);

        // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}