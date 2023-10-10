#include<iostream>
#include<fstream>
#include<bitset>
#include "BitStream.hpp"

using namespace std;

class BitStream {
private:
    std::string file_path;
    std::ofstream file_out;
    std::ifstream file_in;
    char byte_buffer;
    int bit_count;
    bool is_end_of_file;

    void write_byte() {
        file_out.write(&byte_buffer, 1);
        byte_buffer = 0;
        bit_count = 0;
    }

    char read_byte() {
        char byte;
        file_in.read(&byte, 1);
        is_end_of_file = file_in.eof();
        return byte;
    }

public:
    BitStream(const std::string& filePath, std::ios_base::openmode mode) 
        : file_path(filePath), file_out(filePath, mode | std::ios::binary), file_in(filePath, mode | std::ios::binary) {
        byte_buffer = 0;
        bit_count = 0;
        is_end_of_file = false;
    }

    ~BitStream() {
        if (bit_count > 0)
            write_byte();
        file_out.close();
        file_in.close();
    }

    void write_bit(bool bit) {
        if (bit_count == 8)
            write_byte();

        byte_buffer |= (bit << (7 - bit_count));
        bit_count++;
    }

    bool read_bit() {
        if (bit_count == 0) {
            byte_buffer = read_byte();
            if (is_end_of_file)
                return false;
        }

        bool bit = (byte_buffer >> (7 - bit_count)) & 1;
        bit_count++;

        if (bit_count == 8)
            bit_count = 0;

        return bit;
    }

    void write_n_bits(unsigned int value, int num_bits) {
        for (int i = num_bits - 1; i >= 0; --i) {
            bool bit = (value >> i) & 1;
            write_bit(bit);
        }
    }

    std::string read_n_bits(int n) {
        std::string result;
        for (int i = 0; i < n; ++i) {
            bool bit = read_bit();
            if (is_end_of_file)
                break;

            result += bit ? '1' : '0';
        }
        return result;
    }

    bool eof() const {
        return is_end_of_file;
    }
};