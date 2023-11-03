#include <opencv2/opencv.hpp>
#include <iostream>
#include "functions.hpp"

using namespace std;
using namespace cv;

/**
 * @brief Set a watermark on an image with a specified opacity.
 *
 * @param image The image to set the watermark on.
 * @param watermark The watermark to apply to the image.
 * @param opacity The opacity of the watermark (0.0 for fully transparent, 1.0 for fully opaque).
 * @return The watermarked image.
 */

Mat setWatermark(Mat image, Mat watermark, double opacity)
{

    double alpha;
    Mat watermarkedImage;

    alpha = (1.0 - opacity);
    addWeighted(image, alpha, watermark, opacity, 0.0, watermarkedImage);

    return watermarkedImage;
}

/**
 * @brief Convert an RGB image to YUV color space.
 *
 * @param rgbImage The input RGB image.
 * @param yuvImage The output YUV image.
 */

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
/**
 * @brief Convert a YUV image back to RGB color space.
 *
 * @param yuvImage The input YUV image.
 * @param rgbImage The output RGB image.
 */

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

/**
 * @brief Calculate and display the histogram of an image.
 *
 * @param image The input image for which the histogram will be calculated and displayed.
 */

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

/**
 * @brief Apply histogram equalization to an image.
 *
 * @param image The input image to which histogram equalization will be applied.
 */

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


/**
 * @brief Convert a color image to grayscale.
 *
 * @param colorImage The input color image.
 * @param grayscaleImage The output grayscale image.
 */

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

/**
 * @brief Perform 4:2:0 subsampling on a YUV image.
 *
 * @param yuvImage The input YUV image.
 * @param yuvImage420 The output YUV image in 4:2:0 format.
 */

void subSampling420(const cv::Mat &yuvImage, cv::Mat &yuvImage420) {
    // Split YUV image into Y, U, and V channels
    Mat channels[3];
    split(yuvImage, channels);

    if (yuvImage.cols % 2 != 0 || yuvImage.rows % 2 != 0) {
        throw std::runtime_error("Both width and height of the matrix must be even.");
    }

    Size target_size = Size(channels[0].cols, channels[0].rows);  // Mantém o tamanho original

    // Create output matrices for Y, U, and V channels
    Mat y_channel(target_size, CV_8UC1);
    Mat u_channel(target_size, CV_8UC1);
    Mat v_channel(target_size, CV_8UC1);

    // Copia o canal Y original (luma) para o novo canal Y
    channels[0].copyTo(y_channel);

    // Realiza 1/2 de amostragem horizontal e vertical para U e V
    for (int row = 0; row < target_size.height; row += 2) {
        for (int col = 0; col < target_size.width; col += 2) {
            int u_sum = 0;
            int v_sum = 0;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    u_sum += channels[1].at<uchar>(row + i, col + j);
                    v_sum += channels[2].at<uchar>(row + i, col + j);
                }
            }
            u_channel.at<uchar>(row, col) = u_sum / 4;
            v_channel.at<uchar>(row, col) = v_sum / 4;
        }
    }

    // Merge Y, U, and V channels back into a single image
    vector<Mat> merged_channels = {y_channel, u_channel, v_channel};
    merge(merged_channels, yuvImage420);
}

/**
 * @brief Perform 4:2:2 subsampling on a YUV image.
 *
 * @param yuvImage The input YUV image.
 * @param yuvImage422 The output YUV image in 4:2:2 format.
 */

void subSampling422(const cv::Mat &yuvImage, cv::Mat &yuvImage422)
{
    Mat parts[3];
    split(yuvImage, parts);
    float scaling[2];
    if (yuvImage.cols % 2 != 0) {
        throw std::runtime_error("Matrix must have an even number of columns");
    }

    int type = CV_8UC1;
    int interpolation = INTER_LINEAR;

    // Create output matrices for Y, U, and V parts
    Mat y_channel(Size(parts[0].size[1], parts[0].size[0]), type);
    Mat u_channel(Size(parts[0].size[1], parts[0].size[0]), type);
    Mat v_channel(Size(parts[0].size[1], parts[0].size[0]), type);

    // Resize Y channel
    resize(parts[0], y_channel, Size(parts[0].size[1], parts[0].size[0]), 0, 0, interpolation);

    // Resize U and V parts
    resize(parts[1], u_channel, Size(parts[0].size[1], parts[0].size[0]), 0, 0, interpolation);
    resize(parts[2], v_channel, Size(parts[0].size[1], parts[0].size[0]), 0, 0, interpolation);

    // Merge Y, U, and V parts back into a single image
    vector<Mat> merged_parts = {y_channel, u_channel, v_channel};
    merge(merged_parts, yuvImage422);
}

/**
 * @brief Apply a regular blur to an image.
 *
 * @param initial_image The input image to be blurred.
 * @param b1 The first parameter for the blur operation.
 * @param b2 The second parameter for the blur operation.
 * @param blured_image The output blured image.
 */

void regular_blur(Mat& initial_image, int b1, int b2, Mat& blured_image)
{
    blur(initial_image, blured_image, Size(b1, b2));
}

/**
 * @brief Apply a Gaussian blur to an image.
 *
 * @param initial_image The input image to be blurred.
 * @param k1 The first parameter for the Gaussian blur operation.
 * @param k2 The second parameter for the Gaussian blur operation.
 * @param filtered_image The output filtered image.
 */

void gaussian_blur(Mat& initial_image, int k1, int k2, Mat& filtered_image)
{
    GaussianBlur(initial_image, filtered_image, Size(k1, k2), 0, 0);
}