#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Golomb.hpp"

Golomb::Golomb(BitStream* bitStream, int m) {
    this->bitStream = bitStream;
    this->m = m;

    this->parameterB = static_cast<int>(ceil(log2(m)));
    this->parameterL = pow(2, parameterB) - m;
}

Golomb::~Golomb() {
}

void Golomb::encode(int value) {
    int sign = 1;  

    if (value < 0) {
        sign = -1; 
        value = -value; 
    }

    unsigned int q, r;
    q = value / m;
    r = value % m;

    bitStream->writeBit(sign < 0 ? 1 : 0);

    if (r < parameterL) {
        bitStream->writeNBits(r, parameterB - 1);
    } else {
        bitStream->writeNBits(r + parameterL, parameterB);
    }

    while (q--) {
        bitStream->writeBit(1);
    }

    bitStream->writeBit(0);
}

int Golomb::decode() {
    int sign = bitStream->readBit() == 1 ? -1 : 1;

    unsigned int q = 0, r, temporaryValue;

    temporaryValue = bitStream->readNBits(parameterB - 1);
    if (temporaryValue == -1) {
        return -1;
    }

    if (temporaryValue < parameterL) {
        r = temporaryValue;
    } else {
        int additionalBit = bitStream->readNBits(1);
        if (additionalBit == -1) {
            return -1;
        }
        temporaryValue = (temporaryValue << 1) | additionalBit;
        r = temporaryValue - parameterL;
    }

    int tmp;
    while ((tmp = bitStream->readBit()) == 1) {
        q++;
    }

    if (tmp == -1) {
        return -1;
    }

    return (q * m + r) * sign;
}
