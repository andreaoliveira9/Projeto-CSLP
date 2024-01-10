#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "HybridCoding.hpp"

int main(int argc, char const *argv[])
{
    vector<string> files;
    string static_videos = "static/videos/";

    files.push_back("ducks_take_off_444_720p50.y4m");
    files.push_back("park_joy_444_720p50.y4m");
    files.push_back("in_to_tree_444_720p50.y4m");
    files.push_back("old_town_cross_444_720p50.y4m");

    string dir = "build/Deliverable_6/encode_output_lossyHybrid/";
    string command = "mkdir -p " + dir;
    system(command.c_str());

    // Quantization parameters for testing
    int quantization_values[] = {2, 25, 50, 100};
    int periodicity = 5;
    
    for (int i = 0; i < files.size(); i++)
    {
        double original_file_size = 0.0;
        string input = static_videos + files[i];

        ifstream file(input, ifstream::ate | ifstream::binary);
        original_file_size = file.tellg();

        string output_dir = dir + files[i] + "/";
        command = "mkdir -p " + output_dir;
        system(command.c_str());

        for (int searchArea = 3; searchArea <= 5; searchArea++) {
            for (int j = 0; j < sizeof(quantization_values) / sizeof(quantization_values[0]); j++)
            {
                int quantization = quantization_values[j];

                auto start_full = chrono::high_resolution_clock::now(); // start timer
                cout << "Encoding " << files[i] << " with search area " << searchArea << " and quantization " << quantization << endl;

                string output = output_dir + files[i] + "_searchArea_" + to_string(searchArea) + "_quantization_" + to_string(quantization) + ".bin";

                HybridEncoder encoder(input, periodicity, searchArea, quantization, quantization, quantization);

                encoder.encode(output);

                auto end_full = chrono::high_resolution_clock::now(); // end timer
                double time_taken_full = chrono::duration_cast<chrono::nanoseconds>(end_full - start_full).count();
                time_taken_full *= 1e-9;

                double time_to_create_reader = encoder.getTimeToCreateReader();
                time_taken_full -= time_to_create_reader;

                double encoded_file_size = 0.0;
                double average_time = time_taken_full / encoder.getFrameNumber();

                ifstream in(output, ifstream::ate | ifstream::binary);
                encoded_file_size = in.tellg();

                cout << left << setw(20) << "Time Taken"
                    << setw(40) << "Average Time Per Frame (s)"
                    << setw(40) << "Original File Size (MB)"
                    << setw(40) << "Encoded File Size (MB)"
                    << setw(40) << "Compression Rate (%)" << endl;

                cout << left << setw(20) << time_taken_full
                    << setw(40) << average_time
                    << setw(40) << original_file_size / 1000000
                    << setw(40) << encoded_file_size / 1000000
                    << setw(40) << (original_file_size - encoded_file_size) / original_file_size * 100 << endl;
            }
        }
    }

    return 0;
}
