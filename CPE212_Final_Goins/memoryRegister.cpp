//
//  memoryRegister.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryRegister.hpp"

void MemoryRegister::setBinaryEncoding() {
    // cond, op, funct, Rn, Rd, shamt5, sh, '1', Rm
    bitset<6> begin = cat(cond, op);
    build_funct();
    bitset<12> half1 = cat(begin, funct);
    bitset<8> midreg = cat(Rn, Rd);
    
    bitset<7> temp0 = cat(shamt5, sh);
    bitset<5> temp1; // combine a 1 with Rm
    temp1.set(0); // always a 1
    for (int c = 1; c <= 5; c++) {
        if (Rm[c] == 1)
            temp1.set(c);
        else
            temp1.reset(c);
    }
    bitset<12> Src2 = cat(temp0, temp1);
    bitset<20> half2 = cat(midreg, Src2);
    binaryEncoding = cat(half1, half2);
}
