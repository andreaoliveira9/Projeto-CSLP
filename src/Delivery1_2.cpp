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

    Mat frame, yuvFrame, rgbFrame, yuvFrame422, yuvFrame420;
    while (true) {
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, frame, Size(500, 500));

        // Convert RGB to YUV
        rgbToYuv(frame, yuvFrame);

        // Convert YUV back to RGB for display
        yuvToRgb(yuvFrame, rgbFrame);

        // YUV 4:2:0
        subSampling420(yuvFrame, yuvFrame420);

        // TODO: 4:2:2
        subSampling422(yuvFrame, yuvFrame422);

        // Display the frames
        imshow("Original Frame", frame);
        imshow("RGB Frame", rgbFrame);
        imshow("YUV 4:4:4", yuvFrame);
        imshow("YUV 4:2:0", yuvFrame420);
        //imshow("YUV 4:2:2", yuvFrame422);

        // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}