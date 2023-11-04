#ifndef _GOLOMB_
#define _GOLOMB_

#include <stdio.h>

#include "BitStream.hpp"

class Golomb {
public:
	Golomb(BitStream *bs, int m);
	~Golomb();

	void encode(int e);
	int decode();

protected:
	BitStream* bitStream;
  int m;
  int parameterB;
  int parameterL;
};

#endif