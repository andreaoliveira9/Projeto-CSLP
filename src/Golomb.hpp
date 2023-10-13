#ifndef GOLOMB_HPP
#define GOLOMB_HPP

#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include "BitStream.hpp"

using namespace std;

class Golomb {
private:
    int m; // Parameter for Golomb code

public:
    Golomb(int m);
    ~Golomb();

    std::string encode(int num);
    int decode(const std::string& encodedString);
};

#endif // GOLOMB_HPP


