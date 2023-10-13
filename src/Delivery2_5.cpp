#include<iostream>
#include<fstream>
#include "BitStream.cpp"

using namespace std;

int main() {
    // Writing bits to the file
    {
        BitStream bs("example.bin", ios::out);

        bs.write_bit(1);
        bs.write_bit(0); 
        bs.write_n_bits(0b1010, 4);


        bs.write_n_bits(0b111, 3);

        bs.write_bit(1);
        bs.write_bit(0);
        bs.write_n_bits(0b1, 1);
    }

    // Reading bits from the file and printing to console
    {
        BitStream bs("example.bin", ios::in);

        cout << "Reading bits from the file:\n";

        while (true) {
            bool bit = bs.read_bit();
            if (bs.eof())
                break;

            cout << bit;
        }
        cout << "\n\n";
    }

    // Reading bits from the file and printing to console
    {
        BitStream bs("example.bin", ios::in);

        int value = bs.read_n_bits(5);  // Reads 4 bits from the file
        cout << "Read value: " << value << endl;
        value = bs.read_n_bits(6);  // Reads 4 bits from the file
        cout << "Read value: " << value << endl;
        value = bs.read_n_bits(7);  // Reads 4 bits from the file
        cout << "Read value: " << value << endl;

    }

    return 0;
}
