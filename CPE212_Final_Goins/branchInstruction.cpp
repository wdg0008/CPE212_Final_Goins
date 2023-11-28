//
//  branchInstruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "branchInstruction.hpp"

BranchInstruction::BranchInstruction() {
    op = bitset<2>(2);
}

void BranchInstruction::setBinaryEncoding() {
    // cond, op, '1', L, imm24
    for (int a = 0; a <= 3; a++) { // copy the condition of execution into the object's binary encoding
        if (cond[a] == 1) {
            binaryEncoding.set(a);
        } else {
            binaryEncoding.reset(a);
        }
    }
    binaryEncoding.set(4); // first bit of branch op is always 1
    binaryEncoding.reset(5); // second bit of branch op is always 0
    binaryEncoding.set(6); // this bit is always set to 1
    if (L) { // bit 7 corresponds to the L bool indicating a linking branch instruction
        binaryEncoding.set(7);
    } else {
        binaryEncoding.reset(7);
    }
    for (int b = 0; b <= 23; b++) { // copies the target address into the binary encoding of the instruction
        if (imm24[b] == 1) {
            binaryEncoding.set(b+8);
        } else {
            binaryEncoding.reset(b+8);
        }
    }
}

bool BranchInstruction::isLink(string& instruction) { // checks for links, assigns L in the object, and returns it
    (instruction == "BL") ? (L = true) : (L = false); // ternary if statement checks for whether this is a linking branch instruction
    return L;
}

void BranchInstruction::set_imm24(map<string, int>& labels, string target) { // sets the target address of the branch instruction
    imm24 = bitset<24>(labels[target]); // cast the integer mapped to by the string to a bitset of width 24, then store it in the object
}
