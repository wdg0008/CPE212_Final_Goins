//
//  memoryImmediate.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryImmediate.hpp"

void MemoryImmediate::setBinaryEncoding() {
    MemoryInstruction::setBinaryEncoding(); // parent function does first 20 bits
    for (int e = 0; e <= 11; e++) { // set the last 12 bits to imm12
        if (imm12[e] == 1) {
            binaryEncoding.set(e+20);
        } else {
            binaryEncoding.reset(e+20);
        }
    }
}

void MemoryImmediate::set_imm12(string& immString) {
    imm12 = bitset<12>(scrubString(immString)); // cast the int obtained from the cleaned string to a bitset
}
