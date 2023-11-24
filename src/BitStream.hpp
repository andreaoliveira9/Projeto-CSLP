#ifndef _BITSTREAM_
#define _BITSTREAM_

#include <fstream>
#include <iostream>

using namespace std;

/** 
 * @class BitStream
 * @brief Class to read and write bits to a file.
 *
 * This class provides functionalities to handle bit-level operations
 * on files, allowing for both reading and writing of individual bits or multiple bits.
 */
class BitStream
{
public:
    /**
     * @brief Default constructor.
     */
    BitStream();

    /** 
     * @brief Constructor with file name and mode.
     * @param fileName The string containing the name of the file to be processed.
     * @param m The mode for file operations ('w' for write, 'r' for read).
     */
    BitStream(string fileName, string m);

    /**
     * @brief Opens a file for reading.
     * @param fileName The name of the file to be opened.
     */
    void openToRead(string fileName);

    /**
     * @brief Opens a file for writing.
     * @param fileName The name of the file to be opened.
     */
    void openToWrite(string fileName);

    /**
     * @brief Destructor.
     */
    ~BitStream();

    /**
     * @brief Closes the current bitstream.
     */
    void close();

    /**
     * @brief Writes a bit to the bitstream.
     * @param value The bit to be written (0 or 1).
     */
    void writeBit(int value);

    /**
     * @brief Reads a bit from the bitstream.
     * @return The read bit (0 or 1).
     */
    int readBit();

    /**
     * @brief Writes multiple bits to the bitstream.
     * @param value The value to be written.
     * @param nb The number of bits to write.
     */
    void writeNBits(int value, int nb);

    /**
     * @brief Reads multiple bits from the bitstream.
     * @param nb The number of bits to read.
     * @return The value contained in the read bits.
     */
    int readNBits(int nb);

    /**
     * @brief Gets the byte count of processed data.
     * @return The number of bytes processed.
     */
    int getByteCount();

private:
    unsigned char currentByte;  ///< Buffer to store the current byte of data.
    int currentPosition;        ///< Position in the buffer for the next bit operation.
    fstream file;               ///< File stream for reading/writing.
    int mode;                   ///< Mode of operation (0 for read, 1 for write).
    int byteCount;              ///< Counter for the number of bytes processed.

    void writeBufferToFile();   ///< Writes the buffer to the file.
    void readByteFromfile();    ///< Reads the next byte from the file.
};

#endif  // _BITSTREAM_
