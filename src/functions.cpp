#include <opencv2/opencv.hpp>
#include <iostream>
#include "functions.hpp"

using namespace std;
using namespace cv;

// Mat thresholdImage(const Mat& image, int thresholdType, int thresholdValue = 0, int maxBinaryValue = 255)
// {
//     Mat thresholdedImage;

//     threshold(image, thresholdedImage, thresholdValue, maxBinaryValue, thresholdType);

//     return thresholdedImage;
// }

Mat setWatermark(Mat image, Mat watermark, double opacity)
{
    /*
    *   Set the watermark on the image with the given opacity
    *   @param image: The image to set the watermark on
    *   @param watermark: The watermark to set on the image
    *   @param opacity: The opacity of the watermark
    *   @return: The watermarked image
    * 
    */
    double alpha;
    Mat watermarkedImage;

    alpha = (1.0 - opacity);
    addWeighted(image, alpha, watermark, opacity, 0.0, watermarkedImage);

    return watermarkedImage;
}

void rgbToYuv(const cv::Mat &rgbImage, cv::Mat &yuvImage)
{
    // Ensure input image is not empty and is in BGR format
    if (rgbImage.empty() || rgbImage.channels() != 3)
    {
        std::cerr << "Input image is empty or not in BGR format." << std::endl;
        return;
    }

    // Ensure yuvImage has the correct dimensions and type
    yuvImage.create(rgbImage.size(), CV_8UC3);

    for (int i = 0; i < rgbImage.rows; ++i)
    {
        for (int j = 0; j < rgbImage.cols; ++j)
        {
            // Get RGB values
            uchar R = rgbImage.at<cv::Vec3b>(i, j)[2];
            uchar G = rgbImage.at<cv::Vec3b>(i, j)[1];
            uchar B = rgbImage.at<cv::Vec3b>(i, j)[0];

            // Convert RGB to YUV
            yuvImage.at<cv::Vec3b>(i, j)[0] = static_cast<uchar>(0.257 * R + 0.504 * G + 0.098 * B + 16);   // Y
            yuvImage.at<cv::Vec3b>(i, j)[1] = static_cast<uchar>(-0.148 * R - 0.291 * G + 0.439 * B + 128); // U
            yuvImage.at<cv::Vec3b>(i, j)[2] = static_cast<uchar>(0.439 * R - 0.368 * G - 0.071 * B + 128);  // V
        }
    } 

    cvtColor(rgbImage, yuvImage, COLOR_BGR2YUV);
}

void yuvToRgb(const cv::Mat &yuvImage, cv::Mat &rgbImage)
{
    // Ensure input image is not empty and is in YUV format
    if (yuvImage.empty() || yuvImage.channels() != 3)
    {
        std::cerr << "Input image is empty or not in YUV format." << std::endl;
        return;
    }

    // Ensure rgbImage has the correct dimensions and type
    rgbImage.create(yuvImage.size(), CV_8UC3);

    for (int i = 0; i < yuvImage.rows; ++i)
    {
        for (int j = 0; j < yuvImage.cols; ++j)
        {
            // Get YUV values
            double Y = yuvImage.at<cv::Vec3b>(i, j)[0] - 16.0;
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

void calculateAndDisplayHistogram(const cv::Mat &image)
{
    std::vector<cv::Mat> bgrChannels(3);

    // Split the image into BGR components
    cv::split(image, bgrChannels);

    int histSize = 256;       // Number of bins
    float range[] = {0, 256}; // Range for each channel
    const float *histRange = {range};

    bool uniform = true, accumulate = false;

    cv::Mat b_hist, g_hist, r_hist;

    // Calculate histogram for each channel
    cv::calcHist(&bgrChannels[0], 1, nullptr, cv::Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgrChannels[1], 1, nullptr, cv::Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    cv::calcHist(&bgrChannels[2], 1, nullptr, cv::Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

    // Draw the histograms
    int histWidth = 512, histHeight = 400;
    int binWidth = cvRound((double)histWidth / histSize);

    cv::Mat histImage(histHeight, histWidth, CV_8UC3, cv::Scalar(0, 0, 0));

    // Normalize the histograms to be displayed
    cv::normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < histSize; ++i)
    {
        // Draw lines for each histogram
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(b_hist.at<float>(i - 1))),
                 cv::Point(binWidth * (i), histHeight - cvRound(b_hist.at<float>(i))), cv::Scalar(255, 0, 0), 2, 8, 0);
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(g_hist.at<float>(i - 1))),
                 cv::Point(binWidth * (i), histHeight - cvRound(g_hist.at<float>(i))), cv::Scalar(0, 255, 0), 2, 8, 0);
        cv::line(histImage, cv::Point(binWidth * (i - 1), histHeight - cvRound(r_hist.at<float>(i - 1))),
                 cv::Point(binWidth * (i), histHeight - cvRound(r_hist.at<float>(i))), cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    cv::imshow("Histogram", histImage);
    cv::waitKey(0);
}

void applyHistogramEqualization(cv::Mat &image)
{
    // Check if the image is not in the correct format
    if (image.type() != CV_8UC1)
    {
        std::cerr << "Input image is not in the correct format (CV_8UC1)." << std::endl;
        return;
    }

    // Equalize histogram
    cv::equalizeHist(image, image);
}

void convertToGrayscale(const cv::Mat &colorImage, cv::Mat &grayscaleImage)
{
    grayscaleImage.create(colorImage.rows, colorImage.cols, CV_8UC1);

    for (int i = 0; i < colorImage.rows; ++i)
    {
        for (int j = 0; j < colorImage.cols; ++j)
        {
            cv::Vec3b pixel = colorImage.at<cv::Vec3b>(i, j);
            uchar grayValue = static_cast<uchar>(0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0]);
            grayscaleImage.at<uchar>(i, j) = grayValue;
        }
    }
}

void subSampling420(const cv::Mat &yuvImage, cv::Mat &yuvImage420)
{
    Mat channels[3];
    split(yuvImage, channels);
    Size target_size = Size(channels[0].size[1], channels[0].size[0]);
    float scaling[2];
    if (yuvImage.cols % 2 != 0) {
        throw std::runtime_error("Matrix must have an even number of columns");
    }
    // 1/2 horizontal sampling, 1/2 vertical sampling
    scaling[0] = 0.5;
    scaling[1] = 0.5;

    // Create output matrices for Y, U, and V channels
    Mat y_channel(target_size, CV_8UC1);
    Mat u_channel(target_size, CV_8UC1);
    Mat v_channel(target_size, CV_8UC1);

    // Resize Y channel
    resize(channels[0], y_channel, target_size, 0, 0, INTER_LINEAR);

    // Resize U and V channels
    resize(channels[1], u_channel, target_size, 0, 0, INTER_LINEAR);
    resize(channels[2], v_channel, target_size, 0, 0, INTER_LINEAR);

    // Merge Y, U, and V channels back into a single image
    vector<Mat> merged_channels = {y_channel, u_channel, v_channel};
    merge(merged_channels, yuvImage420);
}

void subSampling422(const cv::Mat &yuvImage, cv::Mat &yuvImage422)
{
    Mat channels[3];
    split(yuvImage, channels);
    Size target_size = Size(channels[0].size[1], channels[0].size[0]);
    float scaling[2];
    if (yuvImage.cols % 2 != 0) {
        throw std::runtime_error("Matrix must have an even number of columns");
    }
    // 1/2 horizontal sampling, full vertical sampling
    scaling[0] = 0.5;
    scaling[1] = 1;

    // Create output matrices for Y, U, and V channels
    Mat y_channel(target_size, CV_8UC1);
    Mat u_channel(target_size, CV_8UC1);
    Mat v_channel(target_size, CV_8UC1);

    // Resize Y channel
    resize(channels[0], y_channel, target_size, 0, 0, INTER_LINEAR);

    // Resize U and V channels
    resize(channels[1], u_channel, target_size, 0, 0, INTER_LINEAR);
    resize(channels[2], v_channel, target_size, 0, 0, INTER_LINEAR);

    // Merge Y, U, and V channels back into a single image
    vector<Mat> merged_channels = {y_channel, u_channel, v_channel};
    merge(merged_channels, yuvImage422);
}


void regular_blur(Mat& initial_image, int b1, int b2, Mat& blured_image)
{
    blur(initial_image, blured_image, Size(b1, b2));
}

void gaussian_blur(Mat& initial_image, int k1, int k2, Mat& filtered_image)
{
    GaussianBlur(initial_image, filtered_image, Size(k1, k2), 0, 0);
}