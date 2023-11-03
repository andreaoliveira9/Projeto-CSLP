#include <cmath>
#include <cstdlib>
#include <iostream>
#include "Golomb.hpp"

Golomb::Golomb(BitStream* bitStream, int divisor) {
    this->bitStream = bitStream;
    this->divisor = divisor;

    this->parameterB = static_cast<int>(std::ceil(std::log2(divisor)));
    this->parameterL = std::pow(2, parameterB) - divisor;
    this->parameterH = divisor - parameterL;
}

Golomb::~Golomb() {
}

void Golomb::encode(int value) {
    bool isNegative = false;
    if (value < 0) {
        isNegative = true;
        value = std::abs(value);
    }

    unsigned int quotient, remainder;
    quotient = value / divisor;
    remainder = value % divisor;

    if (isNegative) {
        bitStream->writeBit(1);
    } else {
        bitStream->writeBit(0);
    }

    if (remainder < parameterL) {
        bitStream->writeNBits(remainder, parameterB - 1);
    } else {
        bitStream->writeNBits(remainder + parameterL, parameterB);
    }

    for (unsigned int i = 0; i < quotient; i++) {
        bitStream->writeBit(1);
    }

    bitStream->writeBit(0);
}

int Golomb::decode() {
    bool isNegative = bitStream->readBit();

    unsigned int quotient = 0, remainder, temporaryValue;

    temporaryValue = bitStream->readNBits(parameterB - 1);
    if (temporaryValue == -1) {
        return -1;
    }

    if (temporaryValue < parameterL) {
        remainder = temporaryValue;
    } else {
        int additionalBit = bitStream->readNBits(1);
        if (additionalBit == -1) {
            return -1;
        }
        temporaryValue = (temporaryValue << 1) | additionalBit;
        remainder = temporaryValue - parameterL;
    }

    int tmp;
    while ((tmp = bitStream->readBit()) == 1) {
        quotient++;
    }

    if (tmp == -1) {
        return -1;
    }

    int result = quotient * divisor + remainder;
    if (isNegative) {
        result *= -1;
    }
    return result;
}
