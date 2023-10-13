#include "Golomb.hpp"

Golomb::Golomb(int m) : m(m) {}

Golomb::~Golomb() {}

std::string Golomb::encode(int num) {
    std::string encodedString;
    int quotient = num / m;
    int remainder = num % m;

    // Encode quotient using unary code
    for (int i = 0; i < quotient; ++i)
        encodedString += '1';
    encodedString += '0'; // Separator

    // Encode remainder using binary representation
    std::string remainderBinary = std::bitset<32>(remainder).to_string();
    encodedString += remainderBinary.substr(32 - m);

    return encodedString;
}

int Golomb::decode(const std::string& encodedString) {
    int quotient = 0;
    int i = 0;

    // Decode quotient using unary code
    while (i < encodedString.size() && encodedString[i] == '1') {
        quotient++;
        i++;
    }

    // Separator
    i++;

    // Decode remainder using binary representation
    std::string remainderBinary = encodedString.substr(i, m);
    int remainder = std::stoi(remainderBinary, nullptr, 2);

    return quotient * m + remainder;
}

