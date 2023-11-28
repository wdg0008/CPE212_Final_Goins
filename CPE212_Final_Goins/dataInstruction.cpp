//
//  dataInstruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataInstruction.hpp"

DataInstruction::DataInstruction() {
    op = bitset<2>(0);
    S = false; // assumption I am making that no 'S' prefixes are used
}

void DataInstruction::set_S(bool value) {
    S = value;
}

void DataInstruction::set_I(bool value) {
    I = value;
}

void DataInstruction::set_cmd(string& instruction) {
    if (instruction == "ADD")
        cmd = bitset<4>("0100");
    else if (instruction == "SUB")
        cmd = bitset<4>("0010");
    else if (instruction == "AND")
        cmd = bitset<4>("0000");
    else if (instruction == "ORR")
        cmd = bitset<4>("1100");
    else if (instruction == "CMP") {
        cmd = bitset<4>("1010");
        S = true; // not exactly sure where to do this
    }
    else if (instruction == "MOV" || instruction == "LSL" || instruction == "LSR" || instruction == "ASR" || instruction == "ROR" /* || instruction == "RRX" */)
        cmd = bitset<4>("1101");
    /* // the getInstructionType function guarantees that only valid data instructions have made it thus far
    else
        throw (BadInstruction());
     */
}

void DataInstruction::set_Rn(string& info) {
    Rn = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void DataInstruction::set_Rd(string& info) {
    Rd = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void DataInstruction::setBinaryEncoding() {
    for (int a = 0; a <= 3; a++) { // set first four bits to cond
        if (cond[a] == 1)
            binaryEncoding.set(a);
        else
            binaryEncoding.reset(a);
    }
    binaryEncoding.reset(4); // bits 27 and 26 are the op value, which is 00 for data procesisng
    binaryEncoding.reset(5);
    if (I) {
        binaryEncoding.set(6);
    } else {
        binaryEncoding.reset(6);
    }
    for (int b = 0; b <= 4; b++) { // set bits 24-21 to cmd
        if (cmd[b] == 1)
            binaryEncoding.set(b+7);
        else
            binaryEncoding.reset(b+7);
    }
    if (S) // set bit 20 based on S
        binaryEncoding.set(11);
    else
        binaryEncoding.reset(11);
    for (int d = 0; d <= 3; d++) { // set bits 19-16 to Rn
        if (Rn[d] == 1)
            binaryEncoding.set(d+12);
        else
            binaryEncoding.reset(d+12);
    }
    for (int e = 0; e <= 3; e++) { // set bits 15-12 to Rd
        if (Rd[e] == 1)
            binaryEncoding.set(e+16);
        else
            binaryEncoding.reset(e+16);
    }
    return;
}
