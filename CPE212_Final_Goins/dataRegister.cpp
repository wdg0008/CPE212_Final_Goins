//
//  dataRegister.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataRegister.hpp"

DataRegister::DataRegister() {
    op = 0;
}

void DataRegister::set_Rm(string& info) {
    Rm = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void DataRegister::set_shamt5(string& info) {
    shamt5 = bitset<5>(readImmediate(info)); // clean up the string to get an int and cast to bitset
}

void DataRegister::set_sh(string& info) { // sets the shift type based on the instruction name
    if (info == "MOV" || info == "LSL") // MOV requires special handling, as bits 11-4 are all 0
        sh = 0;
    else if (info == "LSR")
        sh = 1;
    else if (info == "ASR")
        sh = 2;
    else if (info == "ROR" /* || info == "RRX" */) // RRX has the same sh value
        sh = 3;  
}

void DataRegister::setBinaryEncoding() {
    DataInstruction::setBinaryEncoding(); // call the parent virtual function
    for (int f = 0; f <= 4; f++) { // set bits 11-7 to shamt5
        if (shamt5[f] == 1)
            binaryEncoding.set(f+20);
        else
            binaryEncoding.reset(f+20);
    }
    for (int g = 25; g <= 26; g++) { // sets bits 6-5 to sh
        if (sh[g] == 1)
            binaryEncoding.set(g);
        else
            binaryEncoding.reset(g);
    }
    binaryEncoding.reset(27); // always a 0 at bit 4
    for (int h = 0; h <= 4; h++) {
        if (Rm[h] == 1) {
            binaryEncoding.set(h+28);
        } else {
            binaryEncoding.reset(h+28);
        }
    }
    // cond, op, I, cmd, S, Rn, Rd, shamt, sh, '0', Rm
}
