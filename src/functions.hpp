#include <opencv2/opencv.hpp>

cv::Mat setWatermark(cv::Mat image, cv::Mat watermark, double input);

void yuvToRgb(const cv::Mat& yuvImage, cv::Mat& rgbImage);

void rgbToYuv(const cv::Mat& rgbImage, cv::Mat& yuvImage);

void calculateAndDisplayHistogram(const cv::Mat& image);

void applyHistogramEqualization(cv::Mat& image);

void convertToGrayscale(const cv::Mat& colorImage, cv::Mat& grayscaleImage);

void subSampling422(const cv::Mat yuvImage, cv::Mat yuvImage420);

void subSampling422(const cv::Mat yuvImage, cv::Mat yuvImage422);

// void thresholdImage(const cv::Mat& image, cv::Mat& thresholdImage, int thresholdType, int thresholdValue, int maxBinaryValue);