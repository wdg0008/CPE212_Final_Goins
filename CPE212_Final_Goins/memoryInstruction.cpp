//
//  memoryInstruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryInstruction.hpp"

void MemoryInstruction::setBinaryEncoding() {
    for (int a = 0; a <= 3; a++) {
        if (cond[a] == 1) {
            binaryEncoding.set(a);
        } else {
            binaryEncoding.reset(a);
        }
    }
    binaryEncoding.reset(4); // first bit of memory op is always 0
    binaryEncoding.set(5); // second bit of memory op is always 1
    bitset<6> f; // construct the funct
    if (I)
        f.set(0);
    else
        f.reset(0);
    if (P)
        f.set(1);
    else
        f.reset(1);
    if (U)
        f.set(2);
    else
        f.reset(2);
    if (B)
        f.set(3);
    else
        f.reset(3);
    if (W)
        f.set(4);
    else
        f.reset(4);
    if (L)
        f.set(5);
    else
        f.reset(5);
    for (int b = 0; b <= 5; b++) { // sets the funct bits of the instruction
        if (f[b] == 1) {
            binaryEncoding.set(b+6);
        } else {
            binaryEncoding.reset(b+6);
        }
    }
    for (int c = 0; c <= 3; c++) { // set Rn for the memory instruction
        if (Rn[c] == 1) {
            binaryEncoding.set(c+12);
        } else {
            binaryEncoding.reset(c+12);
        }
    }
    for (int d = 0; d <= 3; d++) { // set Rd for the memory instruction
        if (Rd == 1) {
            binaryEncoding.set(d+16);
        } else {
            binaryEncoding.reset(d+16);
        }
    }
}

MemoryInstruction::MemoryInstruction() {
    op = bitset<2>(1); // the op code for memory is always 1
    B = false; // assumption based on the fact that only STR and LDR are implemented
    U = false; // assumption because I think adding negatives works
}

/* These were copied from the data-processing instructions but NOT put in the instruction grandparent class, since branch cannot use them */
void MemoryInstruction::set_Rn(string& info) {
    Rn = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void MemoryInstruction::set_Rd(string& info) {
    Rd = bitset<4>(readRegister(info)); // parse the register string for an unsigned int, then cast to 4 bits
}

void const MemoryInstruction::set_values(string& lineString) {
    // the immediate bit is handled by the child objects that encapsulate this parent
    (lineString.substr(0, 3) == "LDR") ? (L = true) : (L = false); // check for load bit from first 3 chars
    if (!findStringChar(lineString, '[') && !findStringChar(lineString, ']')) {
        // this is operating on a single register or immediate, which is weird
        P = true;
        W = false;
    }
    string::size_type lBracePos = lineString.find('['); // position of the left brace
    string::size_type rBracePos = lineString.find(']'); // position of the right brace
    string::size_type braceDiff = rBracePos-lBracePos;
    string inBraces = lineString.substr(lBracePos,braceDiff);
    if (findStringChar(inBraces, ',')) { // either offset OR pre-index
        P = true;
        (findStringChar(inBraces, '!')) ? (W = true) : (W = false);
        // set the writeback bit by checking for an exclamation point
        // if the '!' is present, it is pre-indexed, which makes W true
    } else {
        // post-index
        P = false;
        W = false;
    }
}
