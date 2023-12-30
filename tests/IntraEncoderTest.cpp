#include <iostream>
#include "opencv2/opencv.hpp"
#include "BitStream.hpp"
#include "intraCoding.hpp"
#include <bitset>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <iterator>
#include "Converter.hpp"
int main(int argc, char const *argv[])
{
    vector<string> files;
    string static_videos = "static/videos/";
    files.push_back("park_joy_420_720p50.y4m");

    // create directory for output
    string dir = "batch_output/";
    string command = "mkdir -p " + dir;
    system(command.c_str());

    Converter conv;


    for (int i = 0; i < files.size(); i++)
    {
        double original_file_size = 0.0;
        string input = static_videos + files[i];

        ifstream in(input, ifstream::ate | ifstream::binary);
        original_file_size = in.tellg();

        // open video file and get header
        ifstream file(input, ios::binary);

        // Read the file header

        string file_header;

        getline(file, file_header);

        // split the file header into tokens

        istringstream iss(file_header);

        vector<string> tokens{istream_iterator<string>{iss},
                              istream_iterator<string>{}};

        // write the tokens to the console
        int format;
        if (tokens.size() > 6)
        {
            if (tokens[6].compare("C444") == 0)
            {
                format = 0;
            }
            else if (tokens[6].compare("C422") == 0)
            {
                format = 1;
            }
        }
        else
        {
            format = 2;
        }

        // print the format

        cout << "Format: " << format << endl;

        string command = "mkdir -p " + dir + files[i];
        system(command.c_str());
        string output = dir + files[i] +  ".bin";

        VideoCapture cap(input);

        if (!cap.isOpened())
        {
            cout << "Error opening video stream or file" << endl;
            return -1;
        }
        int shift = 0;
        GolombEncoder encoder(output);
        IntraEncoder intra_encoder(encoder, shift);

        Mat frame;

        encoder.encode(format);
        encoder.encode(shift);
        int num_frames = cap.get(CAP_PROP_FRAME_COUNT);
        encoder.encode(num_frames);

        int count = 0;
        auto start_full = chrono::high_resolution_clock::now(); // start timer
        switch (format)
        {
        case 0:
        {
            while (true)
            {
                // percentage = (cap.get(CAP_PROP_POS_FRAMES) / num_frames) * 100;
                // cout << "Frame %: " << fixed << setprecision(1) << percentage << "\% ETA ~ " << average_time * (100 - percentage) << "s" << endl;
                cap >> frame;

                if (frame.empty())
                {
                    // cout << "\033[F" << flush;
                    // // clear line
                    // cout << "\033[K" << flush;
                    break;
                }

                frame = conv.rgb_to_yuv444(frame);
                if (count == 0)
                {
                    encoder.encode(frame.cols);
                    encoder.encode(frame.rows);
                }
                // auto start = chrono::high_resolution_clock::now(); // start timer

                intra_encoder.encode(frame);
                // auto end = chrono::high_resolution_clock::now(); // end timer
                // double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

                // time_taken *= 1e-9;

                // average_time *= count;
                // average_time += time_taken;
                // average_time /= ++count;
                // // move to start of previous line
                // cout << "\033[F" << flush;
                // // clear line
                // cout << "\033[K" << flush;
                count++;
            }
        }
        case (1):
        {
            while (true)
            {
                // percentage = (cap.get(CAP_PROP_POS_FRAMES) / num_frames) * 100;
                // cout << "Frame %: " << fixed << setprecision(1) << percentage << "\% ETA ~ " << average_time * (100 - percentage) << "s" << endl;
                cap >> frame;

                if (frame.empty())
                {
                    // cout << "\033[F" << flush;
                    // // clear line
                    // cout << "\033[K" << flush;
                    break;
                }

                frame = conv.rgb_to_yuv422(frame);
                if (count == 0)
                {
                    encoder.encode(frame.cols);
                    encoder.encode(frame.rows);
                }
                // auto start = chrono::high_resolution_clock::now(); // start timer

                intra_encoder.encode(frame);
                // auto end = chrono::high_resolution_clock::now(); // end timer
                // double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

                // time_taken *= 1e-9;

                // average_time *= count;
                // average_time += time_taken;
                // average_time /= ++count;
                // // move to start of previous line
                // cout << "\033[F" << flush;
                // // clear line
                // cout << "\033[K" << flush;
                count++;
            }
        }
        case (2):
        {
            while (true)
            {
                // percentage = (cap.get(CAP_PROP_POS_FRAMES) / num_frames) * 100;
                // cout << "Frame %: " << fixed << setprecision(1) << percentage << "\% ETA ~ " << average_time * (100 - percentage) << "s" << endl;
                cap >> frame;

                if (frame.empty())
                {
                    // cout << "\033[F" << flush;
                    // // clear line
                    // cout << "\033[K" << flush;
                    break;
                }

                frame = conv.rgb_to_yuv420(frame);
                if (count == 0)
                {
                    encoder.encode(frame.cols);
                    encoder.encode(frame.rows);
                }
                // auto start = chrono::high_resolution_clock::now(); // start timer

                intra_encoder.encode(frame);
                // auto end = chrono::high_resolution_clock::now(); // end timer
                // double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

                // time_taken *= 1e-9;

                // average_time *= count;
                // average_time += time_taken;
                // average_time /= ++count;
                // // move to start of previous line
                // cout << "\033[F" << flush;
                // // clear line
                // cout << "\033[K" << flush;
                count++;
            }
        }
        }
        encoder.finishEncoding();

        auto end_full = chrono::high_resolution_clock::now(); // end timer
        double time_taken_full = chrono::duration_cast<chrono::nanoseconds>(end_full - start_full).count();

        time_taken_full *= 1e-9;

        double encoded_file_size = 0.0;

        ifstream in2(output, ifstream::ate | ifstream::binary);
        encoded_file_size = in2.tellg();

        cout << left << setw(20) << "Time Taken"
                //  << setw(20) << "Average Time"
                << setw(40) << "Original File Size (MB)"
                << setw(40) << "Encoded File Size (MB)" << endl;

        cout << left << setw(20) << time_taken_full
                //  << setw(20) << average_time
                << setw(40) << original_file_size / 1000000
                << setw(40) << encoded_file_size / 1000000 << endl;
        
    }
}