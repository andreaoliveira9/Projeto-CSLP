#ifndef _GOLOMB_
#define _GOLOMB_

class Golomb {
public:
	Golomb(BitStream *bs, int m);
	~Golomb();

	void encode(int e);
	int decode();

protected:
	BitStream* bitStream;
  int m;
};

#endif