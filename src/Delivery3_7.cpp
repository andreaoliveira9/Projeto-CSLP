#include "BitStream.cpp"
#include "Golomb.cpp"
#include <iostream>
#include <vector>

int main() {
    // Golomb parameter (m)
    int m = 5;

    // Number to be encoded
    int num = 42;

    // Create a Golomb instance
    Golomb *golombEncoder = new Golomb("encoded.bin", ios::out, m);

    // Encode the number using Golomb coding
    golombEncoder -> encode(num);
    delete golombEncoder;
    
    // Create a Golomb instance for decoding
    Golomb *golombDecoder = new Golomb("encoded.bin", ios::out, m);

    // Decode the number using Golomb coding
    int decodedNum = golombDecoder -> decode();

    std::cout << "Original Number: " << num << std::endl;
    std::cout << "Decoded Number: " << decodedNum << std::endl;

    return 0;
}