#include <opencv2/opencv.hpp>

void rgbToYuv(const cv::Mat& rgbImage, cv::Mat& yuvImage) {
    // Ensure input image is not empty and is in BGR format
    if (rgbImage.empty() || rgbImage.channels() != 3) {
        std::cerr << "Input image is empty or not in BGR format." << std::endl;
        return;
    }

    // Ensure yuvImage has the correct dimensions and type
    yuvImage.create(rgbImage.size(), CV_8UC3);

    for (int i = 0; i < rgbImage.rows; ++i) {
        for (int j = 0; j < rgbImage.cols; ++j) {
            // Get RGB values
            uchar R = rgbImage.at<cv::Vec3b>(i, j)[2];
            uchar G = rgbImage.at<cv::Vec3b>(i, j)[1];
            uchar B = rgbImage.at<cv::Vec3b>(i, j)[0];

            // Convert RGB to YUV
            yuvImage.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(0.257 * R + 0.504 * G + 0.098 * B +  16);  // Y
            yuvImage.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(-0.148 * R - 0.291 * G + 0.439 * B + 128);  // U
            yuvImage.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(0.439 * R - 0.368 * G - 0.071 * B + 128);  // V
        }
    }
}

void yuvToRgb(const cv::Mat& yuvImage, cv::Mat& rgbImage) {
    // Ensure input image is not empty and is in YUV format
    if (yuvImage.empty() || yuvImage.channels() != 3) {
        std::cerr << "Input image is empty or not in YUV format." << std::endl;
        return;
    }

    // Ensure rgbImage has the correct dimensions and type
    rgbImage.create(yuvImage.size(), CV_8UC3);

    for (int i = 0; i < yuvImage.rows; ++i) {
        for (int j = 0; j < yuvImage.cols; ++j) {
            // Get YUV values
            double Y = yuvImage.at<cv::Vec3b>(i, j)[0] -16.0;
            double U = yuvImage.at<cv::Vec3b>(i, j)[1] - 128.0;
            double V = yuvImage.at<cv::Vec3b>(i, j)[2] - 128.0;

            // Convert YUV to RGB
            double R = 1.164 * Y + 1.596 * V;
            double G = 1.164 * Y - 0.392 * U - 0.813 * V;
            double B = 1.164 * Y + 2.017 * U;

            // Ensure RGB values are in the valid range [0, 255]
            R = std::min(std::max(R, 0.0), 255.0);
            G = std::min(std::max(G, 0.0), 255.0);
            B = std::min(std::max(B, 0.0), 255.0);

            // Set RGB values
            rgbImage.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(R);
            rgbImage.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(G);
            rgbImage.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(B);
        }
    }
}

cv::Mat convertToGrayscale(const cv::Mat& colorImage) {
    cv::Mat grayscaleImage(colorImage.rows, colorImage.cols, CV_8UC1);

    for (int i = 0; i < colorImage.rows; ++i) {
        for (int j = 0; j < colorImage.cols; ++j) {
            cv::Vec3b pixel = colorImage.at<cv::Vec3b>(i, j);
            uchar grayValue = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            grayscaleImage.at<uchar>(i, j) = grayValue;
        }
    }

    return grayscaleImage;
}

int main() {
    cv::VideoCapture video("../TestVideo.mp4");

    if (!video.isOpened()) {
        std::cerr << "Failed to open video." << std::endl;
        return -1;
    }

    cv::Mat frame, yuvFrame, rgbFrame;
    while (true) {
        video >> frame;

        if (frame.empty())
            break;

        // Convert RGB to YUV
        rgbToYuv(frame, yuvFrame);

        // 4:4:4 - No subsampling
        // cv::Mat yuv444 = yuvFrame.clone();

        // TODO: 4:2:2

        // TODO: 4:2:0

        // Convert YUV back to RGB for display
        yuvToRgb(yuvFrame, rgbFrame);

        // Convert RGB to grayscale
        cv::Mat grayscaleFrame = convertToGrayscale(frame);

        // Display the frames
        cv::imshow("Video Player", grayscaleFrame);

        // Break the loop if 'q' is pressed
        if (cv::waitKey(30) == 'q')
            break;
    }

    cv::destroyAllWindows();
    return 0;
}

