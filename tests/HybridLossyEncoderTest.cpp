#include <iostream>
#include "opencv2/opencv.hpp"
#include "HybridCoding.hpp"

int main(int argc, char const *argv[])
{
    vector<string> files;
    string static_videos = "static/videos/";

    // files.push_back("ducks_take_off_420_720p50.y4m");
    // files.push_back("park_joy_420_720p50.y4m");
    files.push_back("akiyo_qcif.y4m");

    string dir = "build/Deliverable_6/encode_output_hybrid/";
    string command = "mkdir -p " + dir;
    system(command.c_str());

    int block_range = 3;
    int quantization1 = 50;
    int quantization2 = 50;
    int quantization3 = 50;
    for (int i = 0; i < files.size(); i++)
    {
        double original_file_size = 0.0;
        string input = static_videos + files[i];

        ifstream file(input, ifstream::ate | ifstream::binary);
        original_file_size = file.tellg();

        string command = "mkdir -p " + dir + files[i];
        system(command.c_str());
        auto start_full = chrono::high_resolution_clock::now(); // start timer
        
          cout << "Encoding " << files[i] << " with block range " << block_range <<  endl;
          string output = dir + files[i] + "/" + files[i] + "_lossy_level_" + to_string(quantization1) + ".bin";

          HybridEncoder encoder(input, 20, block_range, quantization1, quantization2, quantization3);

          encoder.encode(output);
          auto end_full = chrono::high_resolution_clock::now(); // end timer
          double time_taken_full = chrono::duration_cast<chrono::nanoseconds>(end_full - start_full).count();

          time_taken_full *= 1e-9;

          double encoded_file_size = 0.0;

          ifstream in(output, ifstream::ate | ifstream::binary);
          encoded_file_size = in.tellg();

          cout << left << setw(20) << "Time Taken"
              //  << setw(20) << "Average Time"
              << setw(40) << "Original File Size (MB)"
              << setw(40) << "Encoded File Size (MB)" << endl;

          cout << left << setw(20) << time_taken_full
              //  << setw(20) << average_time
              << setw(40) << original_file_size / 1000000
              << setw(40) << encoded_file_size / 1000000 << endl;
      
    }
    
    return 0;
}