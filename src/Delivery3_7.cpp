#include <iostream>
#include "Golomb.cpp"

int main() {
    int m = 5; // Parameter for Golomb code

    Golomb golomb(m);

    // Test encoding and decoding
    int numToEncode = 10;
    std::string encodedString = golomb.encode(numToEncode);
    int decodedNum = golomb.decode(encodedString);

    std::cout << "Original Number: " << numToEncode << std::endl;
    std::cout << "Encoded String: " << encodedString << std::endl;
    std::cout << "Decoded Number: " << decodedNum << std::endl;

    // Unit tests
    std::cout << "\nUnit Tests:" << std::endl;

    // Test 1
    int testNum1 = 7;
    std::string encodedString1 = golomb.encode(testNum1);
    int decodedNum1 = golomb.decode(encodedString1);

    std::cout << "Test 1 - Original Number: " << testNum1 << ", Encoded String: " << encodedString1 << ", Decoded Number: " << decodedNum1 << std::endl;

    // Test 2
    int testNum2 = 20;
    std::string encodedString2 = golomb.encode(testNum2);
    int decodedNum2 = golomb.decode(encodedString2);

    std::cout << "Test 2 - Original Number: " << testNum2 << ", Encoded String: " << encodedString2 << ", Decoded Number: " << decodedNum2 << std::endl;

    return 0;
}

