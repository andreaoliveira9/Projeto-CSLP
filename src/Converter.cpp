#include "Converter.hpp"

Converter::Converter() {}

Mat Converter::rgb_to_yuv444(Mat &frame)
{
    int rows = frame.rows, cols = frame.cols;
    int Y, U, V, B, G, R;

    Mat y(rows, cols, CV_8UC1);
    Mat u(rows, cols, CV_8UC1);
    Mat v(rows, cols, CV_8UC1);
    Mat result;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B = frame.ptr<Vec3b>(i)[j][0];
            G = frame.ptr<Vec3b>(i)[j][1];
            R = frame.ptr<Vec3b>(i)[j][2];

            Y = 0.299 * R + 0.587 * G + 0.114 * B;
            U = 128 - 0.168736 * R - 0.331264 * G + 0.5 * B;
            V = 128 + 0.5 * R - 0.418688 * G - 0.081312 * B;

            if (Y < 0)
            {
                Y = 0;
            }
            if (U < 0)
            {
                U = 0;
            }
            if (V < 0)
            {
                V = 0;
            }
            if (Y > 255)
            {
                Y = 255;
            }
            if (U > 255)
            {
                U = 255;
            }
            if (V > 255)
            {
                V = 255;
            }

            y.ptr<uchar>(i)[j] = Y;
            u.ptr<uchar>(i)[j] = U;
            v.ptr<uchar>(i)[j] = V;
        }
    }
    vector<Mat> channels{y, u, v};
    merge(channels, result);
    return result;
}

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

Mat Converter::rgb_to_yuv422(Mat &frame)
{
    int rows = frame.rows, cols = frame.cols;
    int u_col = 0, v_col = 0, u_row = rows, v_row = rows * 3 / 2;
    int Y, U, V, B, G, R;

    Mat result(rows * 2, cols, CV_8UC1);

    for (int i = 0; i < rows; i++)
    {
        if (u_col == cols)
        {
            u_row++;
            u_col = 0;
        }
        if (v_col == cols)
        {
            v_row++;
            v_col = 0;
        }

        for (int j = 0; j < cols; j++)
        {
            B = frame.ptr<Vec3b>(i)[j][0];
            G = frame.ptr<Vec3b>(i)[j][1];
            R = frame.ptr<Vec3b>(i)[j][2];

            Y = 0.299 * R + 0.587 * G + 0.114 * B;
            U = 128 - 0.168736 * R - 0.331264 * G + 0.5 * B;
            V = 128 + 0.5 * R - 0.418688 * G - 0.081312 * B;

            if (Y < 0)
            {
                Y = 0;
            }
            if (U < 0)
            {
                U = 0;
            }
            if (V < 0)
            {
                V = 0;
            }
            if (Y > 255)
            {
                Y = 255;
            }
            if (U > 255)
            {
                U = 255;
            }
            if (V > 255)
            {
                V = 255;
            }

            result.ptr<uchar>(i)[j] = Y;
            if (j % 2 == 0)
            {
                result.ptr<uchar>(u_row)[u_col++] = U;
                result.ptr<uchar>(v_row)[v_col++] = V;
            }
        }
    }
    return result;
}

Mat Converter::yuv422_to_rgb(Mat &frame)
{
    int rows = frame.rows, cols = frame.cols;
    int u_col = 0, v_col = 0, u_row = rows / 2, v_row = u_row * 3 / 2;
    int Y, U, V, B, G, R;

    Mat b(rows / 2, cols, CV_8UC1);
    Mat g(rows / 2, cols, CV_8UC1);
    Mat r(rows / 2, cols, CV_8UC1);
    Mat result;

    for (int i = 0; i < rows / 2; i++)
    {
        if (u_col == cols)
        {
            u_row++;
            u_col = 0;
        }
        if (v_col == cols)
        {
            v_row++;
            v_col = 0;
        }

        for (int j = 0; j < cols; j++)
        {
            Y = frame.ptr<uchar>(i)[j];
            if (j % 2 == 0)
            {
                U = frame.ptr<uchar>(u_row)[u_col++];
                V = frame.ptr<uchar>(v_row)[v_col++];
            }
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

            b.ptr<uchar>(i)[j] = B;
            g.ptr<uchar>(i)[j] = G;
            r.ptr<uchar>(i)[j] = R;
        }
    }
    vector<Mat> channels{b, g, r};
    merge(channels, result);
    return result;
}

Mat Converter::rgb_to_yuv420(Mat &frame)
{
    int rows = frame.rows, cols = frame.cols;
    int Y, U, V, B, G, R;

    Mat result(rows * 3 / 2, cols, CV_8UC1);

    for (int i = 0, u_col = 0, v_col = 0, u_row = rows, v_row = rows * 5 / 4; i < rows; i++)
    {
        if (u_col == cols)
        {
            u_row++;
            u_col = 0;
        }
        if (v_col == cols)
        {
            v_row++;
            v_col = 0;
        }

        for (int j = 0; j < cols; j++)
        {
            B = frame.ptr<Vec3b>(i)[j][0];
            G = frame.ptr<Vec3b>(i)[j][1];
            R = frame.ptr<Vec3b>(i)[j][2];

            Y = 0.299 * R + 0.587 * G + 0.114 * B;
            U = 128 - 0.168736 * R - 0.331264 * G + 0.5 * B;
            V = 128 + 0.5 * R - 0.418688 * G - 0.081312 * B;

            if (Y < 0)
            {
                Y = 0;
            }
            if (U < 0)
            {
                U = 0;
            }
            if (V < 0)
            {
                V = 0;
            }
            if (Y > 255)
            {
                Y = 255;
            }
            if (U > 255)
            {
                U = 255;
            }
            if (V > 255)
            {
                V = 255;
            }

            result.ptr<uchar>(i)[j] = Y;

            if (j % 2 == 0)
            {
                if (i % 2 == 0)
                    result.ptr<uchar>(u_row)[u_col++] = U;
                else
                    result.ptr<uchar>(v_row)[v_col++] = V;
            }
        }
    }
    return result;
}

Mat Converter::yuv420_to_rgb(Mat &frame)
{
    int rows = frame.rows, cols = frame.cols;
    int u_row = rows * 2 / 3, v_row = u_row * 5 / 4;
    int Y1, Y2, U, V, B1, G1, R1, B2, G2, R2;

    Mat b(u_row, cols, CV_8UC1), g(u_row, cols, CV_8UC1), r(u_row, cols, CV_8UC1);
    Mat result;

    for (int i = 0, u_cols = 0, v_cols = 0; i < u_row; i += 2)
    {

        if (u_cols == cols)
        {
            u_row++;
            u_cols = 0;
        }
        if (v_cols == cols)
        {
            v_row++;
            v_cols = 0;
        }

        for (int j = 0; j < cols; j++)
        {
            Y1 = frame.ptr<uchar>(i)[j];
            Y2 = frame.ptr<uchar>(i + 1)[j];

            if (v_row == rows)
                break;

            if (j % 2 == 0)
            {
                U = frame.ptr<uchar>(u_row)[u_cols++];
                V = frame.ptr<uchar>(v_row)[v_cols++];
            }

            B1 = Y1 + 4.06298 * pow(10, -7) * V + 1.772 * U - 226.816;
            G1 = Y1 - 0.714136 * V - 0.344136 * U + 135.459;
            R1 = Y1 + 1.402 * V - 121.889 * pow(10, -6) * U - 179.456;

            B2 = Y2 + 4.06298 * pow(10, -7) * V + 1.772 * U - 226.816;
            G2 = Y2 - 0.714136 * V - 0.344136 * U + 135.459;
            R2 = Y2 + 1.402 * V - 121.889 * pow(10, -6) * U - 179.456;

            if (B1 < 0)
            {
                B1 = 0;
            }
            if (G1 < 0)
            {
                G1 = 0;
            }
            if (R1 < 0)
            {
                R1 = 0;
            }
            if (B1 > 255)
            {
                B1 = 255;
            }
            if (G1 > 255)
            {
                G1 = 255;
            }
            if (R1 > 255)
            {
                R1 = 255;
            }
            if (B2 < 0)
            {
                B2 = 0;
            }
            if (G2 < 0)
            {
                G2 = 0;
            }
            if (R2 < 0)
            {
                R2 = 0;
            }
            if (B2 > 255)
            {
                B2 = 255;
            }
            if (G2 > 255)
            {
                G2 = 255;
            }
            if (R2 > 255)
            {
                R2 = 255;
            }

            b.ptr<uchar>(i)[j] = B1;
            g.ptr<uchar>(i)[j] = G1;
            r.ptr<uchar>(i)[j] = R1;

            b.ptr<uchar>(i + 1)[j] = B2;
            g.ptr<uchar>(i + 1)[j] = G2;
            r.ptr<uchar>(i + 1)[j] = R2;
        }
    }

    vector<Mat> channels{b, g, r};
    merge(channels, result);

    return result;
};
