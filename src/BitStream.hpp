#ifndef BITSTREAM_HPP
#define BITSTREAM_HPP

#include <iostream>
#include <fstream>
#include <bitset>

using namespace std;

/**
 * @class BitStream
 * @brief A class for reading and writing individual bits to a binary file.
 */
class BitStream {
private:
    string file_path; ///< The path to the binary file.
    ofstream file_out; ///< Output file stream for writing.
    ifstream file_in; ///< Input file stream for reading.
    char byte_buffer; ///< Buffer for accumulating bits before writing a byte.
    int bit_count; ///< The count of bits in the byte buffer.
    bool is_end_of_file; ///< Flag indicating the end of the file.

    /**
     * @brief Writes a byte to the binary file.
     */
    void write_byte();

    /**
     * @brief Reads a byte from the binary file.
     *
     * @return The byte read from the file.
     */
    char read_byte();

public:
    /**
     * @brief Constructor for the BitStream class.
     *
     * @param filePath The path to the binary file to read from or write to.
     * @param mode The open mode for the file (e.g., std::ios::in or std::ios::out).
     */
    BitStream(const string& filePath, ios_base::openmode mode);

    /**
     * @brief Destructor for the BitStream class. Closes the file if open.
     */
    ~BitStream();

    /**
     * @brief Writes a single bit to the binary file.
     *
     * @param bit The bit (0 or 1) to write.
     */
    void write_bit(bool bit);

    /**
     * @brief Reads a single bit from the binary file.
     *
     * @return The bit (0 or 1) read from the file.
     */
    bool read_bit();

    /**
     * @brief Writes a specified number of bits to the binary file.
     *
     * @param value The value containing the bits to write.
     * @param num_bits The number of bits to write from the value.
     */
    void write_n_bits(unsigned int value, int num_bits);

    /**
     * @brief Reads a specified number of bits from the binary file.
     *
     * @param n The number of bits to read.
     * @return The value containing the read bits.
     */
    unsigned int read_n_bits(int n);

    /**
     * @brief Checks if the end of the file has been reached.
     *
     * @return true if the end of the file has been reached, false otherwise.
     */
    bool eof() const;
};

#endif // BITSTREAM_HPP
