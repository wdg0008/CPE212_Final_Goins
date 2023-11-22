//
//  dataInstruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataInstruction.hpp"

DataInstruction::DataInstruction() {
    op = bitset<2>(0);
    S = false;
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
    else if (instruction == "MOV" || instruction == "LSL" || instruction == "LSR" || instruction == "ASR" || instruction == "ROR")
        cmd = bitset<4>("1101");
    else
        throw (BadInstruction());
}

void DataInstruction::set_funct() {
    bitset<6> f;
    if (I) // start with the immediate bit
        f.set(0);
    else
        f.reset(0);
    for (int c = 1; c <= 4; c++) { // loop through each index of cmd bitset
        if (cmd[c] == 1) // if the bit is one, then copy it
            f.set(c);
        else
            f.reset(c);
    }
    if (S) // start with the immediate bit
        f.set(5);
    else
        f.reset(5);
    funct = f; // save the funct bitset into the object
    return;
}
