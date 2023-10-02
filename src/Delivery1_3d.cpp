#include<opencv2/opencv.hpp>
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

    Mat frame, grayScaleFrame;
    while (true) {
        video >> frame;

        if (frame.empty())
            break;

        resize(frame, frame, Size(500, 500));

        // Convert the image to grayscale
        convertToGrayscale(frame, grayScaleFrame);

        // Display the frames
        imshow("Grayscale", grayScaleFrame);

        // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}