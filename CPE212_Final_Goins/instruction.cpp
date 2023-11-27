//
//  instruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "instruction.hpp"

void Instruction::setCondition(unsigned int value) {
    if (value >= 15) {
        throw InvalidSize(); // can't do that
    }
    bitset<4> temp(value);
    cond = temp;
}

bitset<4> Instruction::getCondition() {
    return cond;
}

unsigned long Instruction::getDecimalEncoding() {
    return binaryEncoding.to_ulong();
}

Instruction::Instruction() {}; // apparently, this is required even for abstract classes

bitset<32> Instruction::getInstructionWord() {
    return binaryEncoding;
}

string Instruction::getHexEncoding() {
    string binString = binaryEncoding.to_string(); // convert the bits to a string
    string hexString;
    for (int count = 0; count < 7; count++) { // loop through each 4-bit chunk
        string smol = binString.substr(4*count,4); // grab four bits at a time, starting at zero times the loop count
        /* The if statements below are essentially creating the table I look at to convert, since actual math is hard */
        if (smol == "0000") // this should really be a case statement, but C++ dynamic strings do not work like that
            hexString = hexString + '0';
        else if (smol == "0001")
            hexString = hexString + '1';
        else if (smol == "0010")
            hexString = hexString + '2';
        else if (smol == "0011")
            hexString = hexString + '3';
        else if (smol == "0100")
            hexString = hexString + '4';
        else if (smol == "0101")
            hexString = hexString + '5';
        else if (smol == "0110")
            hexString = hexString + '6';
        else if (smol == "0111")
            hexString = hexString + '7';
        else if (smol == "1000")
            hexString = hexString + '8';
        else if (smol == "1001")
            hexString = hexString + '9';
        else if (smol == "1010")
            hexString = hexString + 'A';
        else if (smol == "1011")
            hexString = hexString + 'B';
        else if (smol == "1100")
            hexString = hexString + 'C';
        else if (smol == "1101")
            hexString = hexString + 'D';
        else if (smol == "1110")
            hexString = hexString + 'E';
        else if (smol == "1111")
            hexString = hexString + 'F';
        else
            throw InvalidString();
    }
    return hexString;
}
