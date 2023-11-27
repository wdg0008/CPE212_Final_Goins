//
//  memoryRegister.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryRegister.hpp"

void MemoryRegister::setBinaryEncoding() {
    // cond, op, funct, Rn, Rd, shamt5, sh, '1', Rm
    MemoryInstruction::setBinaryEncoding(); // parent virtual funciton does first 20 bits
    for (int e = 0; e <= 4; e++) { // put shamt5 into the instruction
        if (shamt5[e] == 1) {
            binaryEncoding.set(e+20);
        } else {
            binaryEncoding.reset(e+20);
        }
    }
    for (int f = 0; f <= 1; f++) { // put sh into the instruction
        if (sh[f] == 1) {
            binaryEncoding.set(f+25);
        } else {
            binaryEncoding.reset(f+25);
        }
    }
    binaryEncoding.set(27); // this bit is always set
    for (int g = 0; g <= 3; g++) { // put Rm into the instruction
        if (Rm[g] == 1) {
            binaryEncoding.set(g+28);
        } else {
            binaryEncoding.reset(g+28);
        }
    }
    return;
}

void MemoryRegister::set_Rm(string& info) {
    Rm = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}
