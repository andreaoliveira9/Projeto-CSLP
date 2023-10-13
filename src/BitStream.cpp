#include "BitStream.hpp"

BitStream::BitStream(const std::string& filePath, std::ios_base::openmode mode) 
    : file_path(filePath), file_out(filePath, mode | std::ios::binary), file_in(filePath, mode | std::ios::binary) {
    byte_buffer = 0;
    bit_count = 0;
    is_end_of_file = false;
}

BitStream::~BitStream() {
    if (bit_count > 0)
        write_byte();
    file_out.close();
    file_in.close();
}

void BitStream::write_byte() {
    file_out.write(&byte_buffer, 1);
    byte_buffer = 0;
    bit_count = 0;
}

char BitStream::read_byte() {
    char byte;
    file_in.read(&byte, 1);
    is_end_of_file = file_in.eof();
    return byte;
}

void BitStream::write_bit(bool bit) {
    if (bit_count == 8)
        write_byte();

    byte_buffer |= (bit << (7 - bit_count));
    bit_count++;
}

bool BitStream::read_bit() {
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

void BitStream::write_n_bits(unsigned int value, int num_bits) {
    for (int i = num_bits - 1; i >= 0; --i) {
        bool bit = (value >> i) & 1;
        write_bit(bit);
    }
}

unsigned int BitStream::read_n_bits(int n) {
    unsigned int result = 0;

    for (int i = n - 1; i >= 0; --i) {
        bool bit = read_bit();
        if (is_end_of_file)
            break;

        result |= (bit << i);
    }

    return result;
}

bool BitStream::eof() const {
    return is_end_of_file;
}
