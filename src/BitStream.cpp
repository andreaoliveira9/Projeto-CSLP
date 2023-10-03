#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

class BitStream {
  public:
    string filename;
    char operation;
    fstream inputFile;
    fstream outputFile;
    fstream file;
    unsigned char writeBuffer = 0;
    unsigned char readBuffer = 0;
    int writeCurrentPosition = 0;
    int readCurrentPosition = -1;
    bitset<8> b;

    BitStream(string filename, char operation) {
      this->filename = filename;
      this->operation = operation;

      if (operation == 'w') {
        outputFile.open(filename, ios::binary | ios::out);
      } else if (operation == 'r') {
        inputFile.open(filename, ios::in | ios::binary);
      }
    }

    void closeOutputFile() {
      outputFile.close();
    }

    void closeInputFile() {
      inputFile.close();
    }

    void writeBit(int bit) {
      if (bit == 1) {
        this->writeBuffer |= (1 << this->writeCurrentPosition);
      }

      this->writeCurrentPosition++;

      if (this->writeCurrentPosition == 8) {
        outputFile.write(reinterpret_cast<char*>(&this->writeBuffer), sizeof(this->writeBuffer) * sizeof(char));
        this->writeBuffer = 0;
        this->writeCurrentPosition = 0;
      }
    }

    void writeNBits(int n, int bit) {
      for (int i = 0; i < n; i++) {
        this->writeBit(bit);
      }
    }

    int readBit() {
      if (this->readCurrentPosition == -1 || this->readCurrentPosition == 8) {
        this->inputFile.read(reinterpret_cast<char*>(&this->readBuffer), sizeof(this->readBuffer) * sizeof(char));
        this->readCurrentPosition = 0;
      }

      this->b = bitset<8>(this->readBuffer);
      int bit = this->b[this->readCurrentPosition];
      this->readCurrentPosition++;

      return bit;
    }

    void readNBits(int n) {
      for (int i = 0; i < n; i++) {
        cout << this->readBit() << "\n";
      }
    }

    void readFile() {
      file.open(filename, ios::binary | ios::in);
      char caracter;

      while (file.get(caracter)) {
        for (int i = 0; i < 8; i++)
            cout << ((caracter >> i) & 1);
            cout << "\n";
      }

      file.close();
    }
};