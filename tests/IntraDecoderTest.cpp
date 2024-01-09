#include <iostream>
#include "opencv2/opencv.hpp"
#include "BitStream.hpp"
#include "intraCoding.hpp"
#include "Converter.hpp"

int main(int argc, char const *argv[])
{
    Converter conv;

    cout << "Enter the name of the file to read (absolute path): ";

    string input;

    cin >> input;

    GolombDecoder decoder(input);

    int format = decoder.decode();
    int n_frames = decoder.decode();
    int width = decoder.decode();
    int height = decoder.decode();

    Mat frame;

    IntraDecoder intra_decoder(decoder);

    switch (format)
    {
    case 0:
    {
        while (n_frames > 0)
        {
            frame = Mat::zeros(height, width, CV_8UC3);
            intra_decoder.decode(frame);

            imshow("Image", conv.yuv444_to_rgb(frame));
            if (waitKey(10) == 27)
            {
                destroyAllWindows();
            }; 
            n_frames--;
        }
        break;
    }
    case 1:
    {
        while (n_frames > 0)
        {
            frame = Mat::zeros(height, width, CV_8UC1);
            intra_decoder.decode(frame);

            imshow("Image", conv.yuv422_to_rgb(frame));
            if (waitKey(10) == 27)
            {
                destroyAllWindows();
            }; 
            n_frames--;
        }
        break;
    }
    case 2:
    {
        while (n_frames > 0)
        {
            frame = Mat::zeros(height, width, CV_8UC1);
            intra_decoder.decode(frame);

            imshow("Image", conv.yuv420_to_rgb(frame));
            if (waitKey(10) == 27)
            {
                destroyAllWindows();
            }; 
            n_frames--;
        }
        break;
    }
    }
}