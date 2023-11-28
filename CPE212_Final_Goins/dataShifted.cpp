//
//  dataShifted.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataShifted.hpp"

DataShifted::DataShifted() {
    Rn = 0; // first source register is always 0
    I = false;
}

void DataShifted::setBinaryEncoding() {
    // cond, op, I, cmd, S, Rn, Rd, Rs, '0', sh, '1', Rm
    DataInstruction::setBinaryEncoding();
    binaryEncoding.reset(24);
    for (int f = 0; f <= 1; f++) {
        if (sh[f] == 1) {
            binaryEncoding.set(f+25);
        } else {
            binaryEncoding.reset(f+25);
        }
    }
    binaryEncoding.set(27);
    for (int g = 0; g <= 3; g++) {
        if (Rm[g] == 1) {
            binaryEncoding.set(g+28);
        } else {
            binaryEncoding.reset(g+28);
        }
    }
    return;
}

void DataShifted::set_Rm(string& info) {
    Rm = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void DataShifted::set_Rs(string& info) {
    Rs = bitset<4>(readRegister(info));
}

void DataShifted::set_sh(string& info) { // sets the shift type based on the instruction name
    if (info == "MOV" || info == "LSL") // MOV requires special handling, as bits 11-4 are all 0
        sh = 0;
    else if (info == "LSR")
        sh = 1;
    else if (info == "ASR")
        sh = 2;
    else if (info == "ROR" /* || info == "RRX" */) // RRX has the same sh value
        sh = 3;
}
