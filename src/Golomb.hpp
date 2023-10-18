#ifndef GOLOMB_HPP
#define GOLOMB_HPP

#include "BitStream.hpp"
#include <cmath>

using namespace std;
/**
 * @class Golomb
 * @brief A class for Golomb coding, used for encoding and decoding integers.
 */
class Golomb {
private:
    BitStream* bitStream; ///< A BitStream object for reading and writing bits.
    int m; ///< The Golomb parameter (m value).

public:
    /**
     * @brief Constructor for Golomb class.
     *
     * @param filePath The path to the binary file used for bitstream operations.
     * @param mode The open mode for the file (e.g., std::ios::in or std::ios::out).
     * @param m The Golomb parameter (positive integer).
     */
    Golomb(const string& filePath,ios_base::openmode mode, int m) {
        this -> bitStream = new BitStream(filePath,ios::in|ios::out);
        this -> m = m;
    }

    /**
     * @brief Destructor for the Golomb class. Cleans up resources.
     */
    ~Golomb() {
        delete bitStream;
    }

    /**
     * @brief Encodes an integer using Golomb coding and writes it to the bitstream.
     *
     * @param n The integer to be encoded and written to the bitstream.
     */
    void encode(int n);

    /**
     * @brief Decodes an integer from the bitstream using Golomb coding.
     *
     * @return The decoded integer.
     */
    int decode();
};

#endif // GOLOMB_HPP
