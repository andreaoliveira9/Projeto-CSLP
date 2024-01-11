#include <opencv2/opencv.hpp>

/**
 * @brief Adds a watermark to an image.
 *
 * This function overlays a watermark image on top of the input image with a specified transparency.
 *
 * @param image The input image to which the watermark will be applied.
 * @param watermark The watermark image to overlay.
 * @param input The transparency of the watermark (0.0 for fully transparent, 1.0 for fully opaque).
 * @return The resulting image with the watermark applied.
 */
cv::Mat setWatermark(cv::Mat image, cv::Mat watermark, double input);

/**
 * @brief Converts a YUV image to an RGB image.
 *
 * @param yuvImage The input YUV image.
 * @param rgbImage The output RGB image.
 */
void yuvToRgb(const cv::Mat &yuvImage, cv::Mat &rgbImage);

/**
 * @brief Converts an RGB image to a YUV image.
 *
 * @param rgbImage The input RGB image.
 * @param yuvImage The output YUV image.
 */
void rgbToYuv(const cv::Mat &rgbImage, cv::Mat &yuvImage);

/**
 * @brief Calculates and displays the histogram of an image.
 *
 * @param image The input image for which the histogram will be calculated and displayed.
 */
void calculateAndDisplayHistogram(const cv::Mat &image);

/**
 * @brief Applies histogram equalization to an image.
 *
 * @param image The input image to which histogram equalization will be applied.
 */
void applyHistogramEqualization(cv::Mat &image);

/**
 * @brief Converts a color image to grayscale.
 *
 * @param colorImage The input color image.
 * @param grayscaleImage The output grayscale image.
 */
void convertToGrayscale(const cv::Mat &colorImage, cv::Mat &grayscaleImage);

/**
 * @brief Subsamples a YUV image in 4:2:0 format.
 *
 * @param yuvImage The input YUV image.
 * @param yuvImage420 The subsampled YUV image in 4:2:0 format.
 */
void subSampling420(const cv::Mat &yuvImage, cv::Mat &yuvImage420);

/**
 * @brief Subsamples a YUV image in 4:2:2 format.
 *
 * @param yuvImage The input YUV image.
 * @param yuvImage422 The subsampled YUV image in 4:2:2 format.
 */
void subSampling422(const cv::Mat &yuvImage, cv::Mat &yuvImage422);

/**
 * @brief Applies a regular blur to an image.
 *
 * @param initial_image The input image to be blurred.
 * @param b1 The first parameter for the blur operation.
 * @param b2 The second parameter for the blur operation.
 */
void regular_blur(cv::Mat &initial_image, int b1, int b2);

/**
 * @brief Applies a Gaussian blur to an image.
 *
 * @param initial_image The input image to be blurred.
 * @param k1 The first parameter for the Gaussian blur operation.
 * @param k2 The second parameter for the Gaussian blur operation.
 */
void gaussian_blur(cv::Mat &initial_image, int k1, int k2);
