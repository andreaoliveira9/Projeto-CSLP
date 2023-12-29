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

/** \class Converter
 * 	\brief Class used to convert frames between rbg, yuv444, yuv422 and yuv420 formats.
 */
class Converter
{
private:
public:
    /** \fn Converter
     * 	\brief Constructor for Converter objects.
     */
    Converter();

    /** \fn rgb_to_yuv420
     * 	\brief Converts an rgb frame to yuv420 format.
     *
     *	\param frame RGB frame that will be converted.
     *	\return yuv420 frame converted from RGB.
     */
    Mat rgb_to_yuv420(Mat &frame);

    /** \fn yuv420_to_rgb
     * 	\brief Converts a yuv420 frame to RGB format.
     *
     *	\param frame yuv420 frame that will be converted.
     *	\return RGB frame converted from yuv420.
     */
    Mat yuv420_to_rgb(Mat &frame);

    /** \fn rgb_to_yuv422
     * 	\brief Converts an rgb frame to yuv422 format.
     *
     *	\param frame RGB frame that will be converted.
     *	\return yuv422 frame converted from RGB.
     */
    Mat rgb_to_yuv422(Mat &frame);

    /** \fn yuv422_to_rgb
     * 	\brief Converts a yuv422 frame to RGB format.
     *
     *	\param frame yuv422 frame that will be converted.
     *	\return RGB frame converted from yuv422.
     */
    Mat yuv422_to_rgb(Mat &frame);

    /** \fn rgb_to_yuv444
     * 	\brief Converts an rgb frame to yuv444 format.
     *
     *	\param frame RGB frame that will be converted.
     *	\return yuv444 frame converted from RGB.
     */
    Mat rgb_to_yuv444(Mat &frame);

    /** \fn yuv444_to_rgb
     * 	\brief Converts a yuv444 frame to RGB format.
     *
     *	\param frame yuv444 frame that will be converted.
     *	\return RGB frame converted from yuv444.
     */
    Mat yuv444_to_rgb(Mat &frame);
};
#endif