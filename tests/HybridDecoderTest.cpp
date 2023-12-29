#include "HybridCoding.hpp"

int main(int argc, char const *argv[])
{
    cout << "Enter the name of the file to read from (absolute path): ";

    string input;

    cin >> input;

    cout << "Enter the name of the file to save to (absolute path): ";

    string output;

    cin >> output;

    HybridDecoder decoder(input);

    auto start = chrono::high_resolution_clock::now();

    decoder.decode(output);

    auto end = chrono::high_resolution_clock::now();

    cout << "Decoding took "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;

    return 0;
}
