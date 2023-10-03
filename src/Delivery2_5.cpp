#include<iostream>
#include<fstream>
#include "BitStream.cpp"

using namespace std;

int main(void)
{

    BitStream bsw("test.bin", 'w');
    
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(0);
    
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(1);
    bsw.writeBit(0);
    bsw.writeBit(1);
    bsw.writeBit(1); 
    

    bsw.closeOutputFile(); 

    BitStream bsr("test.bin", 'r');
    
    bsr.readFile();
    
    cout << "Reading the first 3 bits, individually" << "\n";
    cout << bsr.readBit() << "\n";
    cout << bsr.readBit() << "\n";
    cout << bsr.readBit() << "\n";
    
    cout << "\n";
    

    cout << "Reading the first 11 bits" << "\n";
    
    bsr.readNBits(11);
    cout << "\n"; 

    cout << "Writing int 3 in 6 bits" << "\n";
    bsw.writeNBits(3,6);
    bsw.closeOutputFile();
    

    bsr.readFile();
}