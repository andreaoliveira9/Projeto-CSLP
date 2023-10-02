#include<opencv2/opencv.hpp>
#include<iostream>
#include <string>
#include "functions.cpp"

using namespace cv;
using namespace std;

int main(void)
{ 
    Mat watermarkImage, watermarkedImage, resizedFrame, resizedImage;

    double opacity;
    cout << "Enter opacity [0.0 - 1.0]: ";
    cin >> opacity;

    while (opacity < 0 || opacity > 1) 
    {
      cout << "Error! Opacity should be between 0 and 1...\n\n"; 
      cout << "Enter opacity [0.0 - 1.0]: ";
      cin >> opacity;
    }

    VideoCapture video("../../vid/akiyo_qcif.y4m"); 
    if (!video.isOpened()) {
        cerr << "Failed to open video." << endl;
        return -1;
    }

    watermarkImage = imread("../../img/beer.png");
    if (watermarkImage.data == 0) 
    {
      cout << "Error! No image found...\n\n"; 
      return -1;
    }

    resize(watermarkImage, resizedImage, Size(256, 256));

    Mat frame;
    while (true) {
      video >> frame;

      if (frame.empty())
          break;

      resize(frame, resizedFrame, Size(256, 256));

      watermarkedImage = setWatermark(resizedFrame, resizedImage, opacity);

      // Display the resulting frame
      imshow("Watermarked Video", watermarkedImage);

      // Break the loop if 'q' is pressed
        if (waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}