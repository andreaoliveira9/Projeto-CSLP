#ifndef GOLOMB_HPP
#define GOLOMB_HPP

#include "BitStream.hpp"
#include <cmath>

using namespace std;

class Golomb {
private:
    BitStream* bitStream; 
    int m; 

public:
    Golomb(const string& filePath,ios_base::openmode mode, int m) {
        this -> bitStream = new BitStream(filePath,ios::in|ios::out);
        this -> m = m;
    }
    ~Golomb() {delete bitStream;}

    void encode(int n);
    int decode();
};

#endif // GOLOMB_HPP



