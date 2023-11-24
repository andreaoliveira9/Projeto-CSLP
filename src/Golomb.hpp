#ifndef _GOLOMB_
#define _GOLOMB_

/**
 * @class Golomb
 * @brief Class for Golomb coding, a lossless data compression method.
 *
 * Golomb coding is particularly suited for geometrically distributed integer streams.
 * This class provides functionality to encode and decode such streams.
 */
class Golomb {
public:
    /**
     * @brief Constructs a Golomb coding object.
     * 
     * Initialises a Golomb encoder/decoder with a specific bit stream and parameter 'm'.
     * 
     * @param bs Pointer to the BitStream object used for reading/writing encoded data.
     * @param m The parameter 'm' in Golomb coding, related to the distribution of the input values.
     */
	Golomb(BitStream *bs, int m);

    /**
     * @brief Destructor for the Golomb class.
     */
	~Golomb();

	/**
     * @brief Encodes an integer using Golomb coding.
     * 
     * @param e The integer to be encoded.
     */
	void encode(int e);

	/**
     * @brief Decodes and returns the next integer from the bit stream.
     * 
     * @return int The decoded integer.
     */
	int decode();

protected:
    BitStream* bitStream;  ///< Pointer to the bit stream used for encoding/decoding.
    int m;                 ///< The parameter 'm' used in Golomb coding.
};

#endif