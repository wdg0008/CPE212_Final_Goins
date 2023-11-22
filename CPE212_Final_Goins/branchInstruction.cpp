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
    bitset<6> begin = cat(cond, op);
    bitset<2> mid;
    mid.set(0);
    if (L) {
        mid.set(1);
    } else {
        mid.reset(1);
    }
    bitset<8> half1 = cat(begin, mid);
    binaryEncoding = cat(half1, imm24);
}
