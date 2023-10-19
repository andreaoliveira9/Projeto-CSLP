#include "Golomb.hpp"

Golomb::Golomb(const string& filePath, ios_base::openmode mode, int m) {
    this -> bitStream = new BitStream(filePath, ios::in | ios::out);
    this -> m = m;
}

Golomb::~Golomb() {
    delete bitStream;
}

void Golomb::encode(int n) {
    if (m <= 0) {
        throw invalid_argument("Value of m unknown or invalid");
    }

    int sign = 1;  // Default to positive

    if (n < 0) {
        sign = -1;  // Set the sign to negative
        n = -n;      // Make n positive for encoding
    }

    int q = n / m;
    int r = n % m;

    // Encode the sign (1 for negative, 0 for positive)
    bitStream->write_bit(sign < 0 ? 1 : 0);

    // Encode q using unary coding
    while (q--)
        bitStream->write_bit(1);
    bitStream->write_bit(0);

    // Encode r using binary encoding
    int k = static_cast<int>(log2(m));
    bitStream->write_n_bits(r, k);
}

int Golomb::decode() {
    if (m <= 0) {
        throw invalid_argument("Value of m unknown or invalid");
    }

    // Decode the sign
    int sign = bitStream->read_bit() == 1 ? -1 : 1;

    // Decode q using unary coding
    int q = 0;
    while (bitStream->read_bit())
        q++;

    // Decode r using binary decoding
    int k = static_cast<int>(log2(m));
    int r = bitStream->read_n_bits(k);

    // Calculate the magnitude
    int magnitude = q * m + r;

    // Combine the sign and magnitude to get the original value
    return sign * magnitude;
}
