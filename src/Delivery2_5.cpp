#include<iostream>
#include<fstream>
#include "BitStream.cpp"

int main() {
    // Writing bits to the file
    {
        BitStream bs("example.bin", std::ios::out);

        bs.write_bit(1);
        bs.write_bit(0); 
        bs.write_n_bits(0b1010, 4);


        bs.write_n_bits(0b111, 3);

        bs.write_bit(1);
        bs.write_bit(0);
        bs.write_n_bits(0b1011, 4);
    }

    // Reading bits from the file and printing to console
    {
        BitStream bs("example.bin", std::ios::in);

        std::cout << "Reading bits from the file:\n";

        while (true) {
            bool bit = bs.read_bit();
            if (bs.eof())
                break;

            std::cout << bit;
        }
        std::cout << "\n";
    }

    // Reading bits from the file and printing to console
    {
        BitStream bs("example.bin", std::ios::in);

        std::string value = bs.read_n_bits(5);  // Reads 4 bits from the file
        std::cout << "Read value: " << value << std::endl;

    }

    return 0;
}
