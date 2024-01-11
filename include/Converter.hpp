/**
 * @file Converter.hpp
 * @brief Class used to convert frames between RGB, YUV444, YUV422, and YUV420 formats
 *
 * This file contains the declaration of the Converter class used for converting frames between different formats.
 */

#ifndef FORMATCONVERTER_H
#define FORMATCONVERTER_H

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/** @class Converter
 * 	@brief Class used to convert frames between rbg, yuv444, yuv422 and yuv420 formats.
 */
class Converter
{
private:
public:
    /** @fn Converter
     * 	@brief Constructor for Converter objects.
     */
    Converter();

    /** @fn yuv444_to_rgb
     * 	@brief Converts a yuv444 frame to RGB format.
     *
     *	@param frame yuv444 frame that will be converted.
     *	@return RGB frame converted from yuv444.
     */
    Mat yuv444_to_rgb(Mat &frame);
};
#endif