#include "BitStream.hpp"
#include <iostream>

BitStream::BitStream(string fileName, string fileMode) {
    if (fileMode == "read") {
        openToRead(fileName);
    } else {
        openToWrite(fileName); 
    }
}

void BitStream::openToRead(string fileName) {
		mode = 0;
		file.open(fileName.c_str(), fstream::in | fstream::binary);

		if (!file)
				cerr << "Erro ao abrir o arquivo" << endl;

		currentPosition = 0;
		currentByte = 0;
		byteCount = 0;
}

void BitStream::openToWrite(string fileName) {
		mode = 1;
		file.open(fileName.c_str(), fstream::out | fstream::binary);

		if (!file)
				cerr << "Erro ao abrir o arquivo" << endl;

		currentPosition = 0;
		currentByte = 0;
		byteCount = 0;
}

BitStream::BitStream() {
    currentPosition = 0;
    currentByte = 0;
    byteCount = 0;
}

BitStream::~BitStream() {
    close();
}

int BitStream::getByteCount() {
		return byteCount;
}

void BitStream::close() {
    if (mode == 1) {
        writeBufferToFile();
    }
    file.close();
}

void BitStream::writeBit(int value) {
    if (currentPosition == 0) {
        currentPosition = 1;
    }

    if (currentPosition == 256) {
				writeBufferToFile();
        currentPosition = 1;
        currentByte = 0;
        byteCount++;
    }

    currentByte = currentByte | (value * currentPosition);
    currentPosition = currentPosition << 1;
}

int BitStream::readBit() {
    if (currentPosition == 256 || currentPosition == 0) {
        readByteFromfile();
        if (!file) {
            return -1;
        }
        currentPosition = 1;
    }

    int bit = (currentByte & currentPosition) != 0 ? 1 : 0;
    currentPosition = currentPosition << 1;
    return bit;
}

void BitStream::writeNBits(int value, int numBits) {
    while (numBits--) {
        writeBit((value >> numBits) & 1);
    }
}

int BitStream::readNBits(int numBits) {
    int bits = 0;

    while (numBits--) {
        int bit = readBit();

        if (bit == -1) {
            return -1;
        }

        bits = (bits << 1) | bit;
    }

    return bits;
}

void BitStream::writeBufferToFile() {
		file.write(reinterpret_cast<char *>(&currentByte), sizeof(char));
}

void BitStream::readByteFromfile() {
		file.read(reinterpret_cast<char *>(&currentByte), sizeof(char));
}
