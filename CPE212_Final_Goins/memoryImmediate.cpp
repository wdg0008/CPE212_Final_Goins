//
//  memoryImmediate.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryImmediate.hpp"

void MemoryImmediate::setBinaryEncoding() {
    bitset<6> begin = cat(cond, op);
    build_funct();
    bitset<12> half1 = cat(begin, funct);
    bitset<8> midreg = cat(Rn, Rd);
    bitset<20> half2 = cat(midreg, imm12);
    binaryEncoding = cat(half1, half2);
}
