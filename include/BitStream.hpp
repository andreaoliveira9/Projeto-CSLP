/**
 * @file BitStream.hpp
 * @brief Header file for the BitStream class
 *
 * This file contains the definition of the BitStream class, which is used to read and write bits from and to a file.
 */
#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

/** \class BitStream
 *	\brief Class that performs operations with bits.
 *
 *	A class used to read/ write bits from/ to a file.
 *	Minimum amount of data that can be accessed is 1 byte.
 */
class BitStream
{
private:
    /** Buffer where the 8 bits being written/ read are temporarily stored. */
    unsigned char buff;

    /** Number of bits written to/ read from the buffer. */
    int bitCount;

    /** True if the end of the currently open file has been reached. */
    bool eof;

    /** 0 if the current object is being used for reading bits, 1 if it is being used to write bits. */
    int mode;

    /** File pointer */
    fstream fp;

public:
    /**	\fn 	setToRead
     *	\brief 	Opens a file for reading, defining mode as 0 and resets the buffer and bitCount.
     *
     *	\param	file	Path to the file that will be opened for reading.
     *	\return	0 if the file is successfully opened, -1 if not
     */
    int setToRead(string file);

    /**	\fn 	setToWrite
     *	\brief 	Opens a file for writing, defining mode as 1 and resets the buffer and bitCount.
     *
     *	\param	file	Path to the file that will be opened for writing.
     *	\return	0 if the file is successfully opened, -1 if not
     */
    int setToWrite(string file);

    /** \fn 	close
     *	\brief 	Closes the currently opened file, flushing the write buffer if needed.
     *	If the current file is opened for writting and the buffer is not yet complete,
     *	writes 0's until the buffer is flushed, then closes the file pointer.
     */
    void close();

    /** \fn		inputFileIsOpen
     * 	\brief	Checks whether the instace is set to read and a file is open.
     *
     * 	\return	True if the instance is set to read and a file is open, False otherwise
     */
    bool inputFileIsOpen();

    /**	\fn		getEOF
     * 	\brief	Get method for eof variable.
     * 	\return	Value of eof variable
     */
    bool getEOF();

    /** \fn 	writeBit
     *	\brief 	Write a bit to the output file
     *	Adds the bit to a buffer until a full byte has been created.
     *	Once the buffer had 8 bits, the byte is written to the output file and the buffer is reset.
     *
     *	\param bit Bit (0 or 1) that will be written
     */
    void writeBit(int bit);

    /** \fn 	writeNBits
     *	\brief 	Method used write a number to a file using a given number of bits.
     *	Calculates the needed padding of zeros (nBits minus number of bits
     *	the number actually requires), writting them to the file,
     *	then writes the number given using the remaining bits.
     *
     *	\param number 	Number that will be written to file
     *	\param nBits 	Number of bits used to write the given number
     */
    void writeNBits(int number, int nBits);

    /** \fn 	readBit
     *	\brief 	Method used to read 1 bit from the input file.
     *
     *	\return Returns 0 or 1 based on bit value, 2 if an error occurs
     */
    unsigned char readBit();

    /** \fn		readNBits
     *	\brief  Method used to read N bits from the input file.
     *	Calls method readBit 'nBits' times and stores data to an unsigned int.
     *
     *	\param nBits number of bits to read
     *	\return Returns an unsigned int corresponding to the read bits, if an error occurs returns -1.
     */
    unsigned int readNBits(int nBits);
};
#endif