#include "Golomb.hpp"

void Golomb::encode(int n) {
    if (m <= 0) {
        throw invalid_argument("Value of m unknown or invalid");
    }

    int q = n / m;
    int r = n % m;

    // Encode q using unary coding
    while (q--)
        bitStream -> write_bit(1);
    bitStream -> write_bit(0);

    // Encode r using binary encoding
    int k = static_cast<int>(log2(m));
    bitStream -> write_n_bits(r, k);
}

int Golomb::decode() {
    if (m <= 0) {
        throw invalid_argument("Value of m unknown or invalid");
    }

    // Decode q using unary coding
    int q = 0;
    while (bitStream -> read_bit())
        q++;

    // Decode r using binary decoding
    int k = static_cast<int>(log2(m));
    int r = bitStream -> read_n_bits(k);

    return q * m + r;
}