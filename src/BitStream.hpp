#ifndef BITSTREAM_HPP
#define BITSTREAM_HPP

#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

class BitStream {
private:
    std::string file_path;
    std::ofstream file_out;
    std::ifstream file_in;
    char byte_buffer;
    int bit_count;
    bool is_end_of_file;

    void write_byte();
    char read_byte();

public:
    BitStream(const std::string& filePath, std::ios_base::openmode mode);
    ~BitStream();

    void write_bit(bool bit);
    bool read_bit();
    void write_n_bits(unsigned int value, int num_bits);
    std::string read_n_bits(int n);
    bool eof() const;
};

#endif // BITSTREAM_HPP