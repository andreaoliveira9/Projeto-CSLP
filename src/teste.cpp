#include<iostream>
#include<fstream>
#include "BitStream.cpp"

int main() {
    // Writing bits to the file
    /* BitStream bs("example.bin", std::ios::out);

    bs.write_bit(1);
    bs.write_bit(0); 
    bs.write_n_bits(0b10110, 5);
    bs.write_n_bits(0b10110, 5);
    bs.write_n_bits(0b101011, 6);
    bs.write_n_bits(0b1011, 4);
    bs.write_n_bits(0b11010, 5);
    for (int i = 0; i < 100; i++)
        bs.write_n_bits(0b11010, 5);

    bs.write_n_bits(0b111, 3);

    bs.write_bit(1);
    bs.write_bit(0);
    bs.write_n_bits(0b1, 1); */

    BitStream bs("encoded.bin", std::ios::in);

    std::cout << "Reading bits from the file:\n";

    while (true) {
        bool bit = bs.read_bit();
        if (bs.eof())
            break;

        std::cout << bit;
    }
    std::cout << "\n\n";

    return 0;
}
