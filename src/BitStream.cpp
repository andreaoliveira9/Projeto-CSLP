#include "BitStream.hpp"

int BitStream::setToRead(string file)
{
    fp.close();
    fp.open(file, fstream::binary | fstream::in);
    if (!fp.is_open())
    {
        cerr << "Couldn't open specified file for read!" << endl;
        exit(1);
    }

    mode = 0;
    buff = 0;
    bitCount = 8;
    eof = false;

    return 0;
}

int BitStream::setToWrite(string file)
{
    fp.close();
    fp.open(file, fstream::binary | fstream::out | fstream::app);
    if (!fp.is_open())
    {
        cerr << "Couldn't open specified file for write!" << endl;
        exit(1);
    }

    mode = 1;
    buff = 0;
    bitCount = 0;

    return 0;
}

void BitStream::writeBit(int bit)
{
    if (!fp.is_open())
    {
        cerr << "No output file is currently open." << endl;
        // exit program
        exit(1);
    }
    buff |= bit << (7 - bitCount);
    bitCount++;

    if (bitCount == 8)
    {
        fp.write(reinterpret_cast<char *>(&buff), sizeof(unsigned char));
        bitCount = 0;
        buff = 0;
    }
}

void BitStream::writeNBits(int number, int nBits)
{
    if (!fp.is_open())
    {
        cerr << "No input file is currently open." << endl;
        exit(1);
    }
    int sizeNumber = 32 - __builtin_clz(number);

    if (sizeNumber > nBits)
    {
        cout << "Número insuficiente de bits." << endl;
        exit(1);
    }

    for (int n = 0; n < sizeNumber; n++)
        writeBit((number >> n) & 1);

    for (int n = 0; n < nBits - sizeNumber; n++)
        writeBit(0);
}

unsigned char BitStream::readBit()
{
    if (mode)
    {
        cerr << "Bitstream is not in read mode!" << endl;
        exit(1);
    }
    if (!fp.is_open())
    {
        cout << "No input file is currently open." << endl;
        exit(1);
    }

    if (bitCount == 8)
    {
        fp.read(reinterpret_cast<char *>(&buff), sizeof(char));

        if (!fp)
        {
            eof = true;
            cout << "End of File." << endl;
            return 2;
        }
        bitCount = 0;
    }

    unsigned char bit = 1 & (buff >> (7 - bitCount));
    bitCount++;

    return bit;
}

unsigned int BitStream::readNBits(int nBits)
{
    if (!fp.is_open())
    {
        cout << "No input file is currently open." << endl;
        exit(1);
    }
    unsigned char bit;
    unsigned int result = 0;

    for (int i = 0; i < nBits; i++)
    {
        bit = readBit();

        if (bit == 2)
            return -1;

        result |= bit << i;
    }

    return result;
}

void BitStream::close()
{
    if (mode && bitCount != 0)
    {
        while (bitCount)
            writeBit(0);
    }
    fp.close();
}

bool BitStream::inputFileIsOpen()
{
    return mode == 0 && fp.is_open();
}

bool BitStream::getEOF()
{
    return eof;
}