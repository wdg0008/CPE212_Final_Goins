//
//  memoryInstruction.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "memoryInstruction.hpp"

void MemoryInstruction::build_funct() {
    bitset<6> f;
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
    funct = f; // store the bitset to the member
}

MemoryInstruction::MemoryInstruction() {
    op = bitset<2>(1);
}
