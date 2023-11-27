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
    for (int a = 0; a <= 3; a++) {
        if (cond[a] == 1) {
            binaryEncoding.set(a);
        } else {
            binaryEncoding.reset(a);
        }
    }
    binaryEncoding.set(4); // first bit of branch op is always 1
    binaryEncoding.reset(5); // second bit of branch op is always 0
    binaryEncoding.set(6); // this bit is always set to 1
    if (L) {
        binaryEncoding.set(7);
    } else {
        binaryEncoding.reset(7);
    }
    for (int b = 0; b <= 23; b++) {
        if (imm24[b] == 1) {
            binaryEncoding.set(b+8);
        } else {
            binaryEncoding.reset(b+8);
        }
    }
}

bool BranchInstruction::isLink(string& instruction) { // checks for links, assigns L in the object, and returns it
    if (instruction == "BL")
        L = true;
    else // this is a branch and doesn't link, so it must be 'B'
        L = false;
    return L;
}
