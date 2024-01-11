#include "Converter.hpp"

Converter::Converter() {}

Mat Converter::yuv444_to_rgb(Mat &frame)
{
    int Y, U, V, B, G, R;

    Mat result(frame.rows, frame.cols, CV_8UC3);

    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            Y = frame.ptr<Vec3b>(i)[j][0];
            U = frame.ptr<Vec3b>(i)[j][1];
            V = frame.ptr<Vec3b>(i)[j][2];

            B = Y + 4.06298 * pow(10, -7) * V + 1.772 * U - 226.816;
            G = Y - 0.714136 * V - 0.344136 * U + 135.459;
            R = Y + 1.402 * V - 121.889 * pow(10, -6) * U - 179.456;

            if (B < 0)
            {
                B = 0;
            }
            if (G < 0)
            {
                G = 0;
            }
            if (R < 0)
            {
                R = 0;
            }
            if (B > 255)
            {
                B = 255;
            }
            if (G > 255)
            {
                G = 255;
            }
            if (R > 255)
            {
                R = 255;
            }

            result.ptr<Vec3b>(i)[j][0] = B;
            result.ptr<Vec3b>(i)[j][1] = G;
            result.ptr<Vec3b>(i)[j][2] = R;
        }
    }
    return result;
}