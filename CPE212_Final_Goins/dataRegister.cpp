//
//  dataRegister.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataRegister.hpp"

void DataRegister::setBinaryEncoding() {
    for (int a = 0; a <= 3; a++) { // set first four bits to cond
        if (cond[a] == 1)
            binaryEncoding.set(a);
        else
            binaryEncoding.reset(a);
    }
    binaryEncoding.reset(4); // bits 27 and 26 are the op value, which is 00 for data procesisng
    binaryEncoding.reset(5);
    if (I) {
        binaryEncoding.set(6);
    } else {
        binaryEncoding.reset(6);
    }
    for (int b = 7; b <= 11; b++) { // set bits 24-21 to cmd
        if (cmd[b] == 1)
            binaryEncoding.set(b);
        else
            binaryEncoding.reset(b);
    }
    if (S) // set bit 20 based on S
        binaryEncoding.set(11);
    else
        binaryEncoding.reset(11);
    for (int d = 12; d <= 15; d++) { // set bits 19-16 to Rn
        if (Rn[d] == 1)
            binaryEncoding.set(d);
        else
            binaryEncoding.reset(d);
    }
    for (int e = 16; e <= 19; e++) { // set bits 15-12 to Rd
        if (Rd[e] == 1)
            binaryEncoding.set(e);
        else
            binaryEncoding.reset(e);
    }
    
    for (int f = 20; f <= 24; f++) { // set bits 11-7 to shamt5
        if (shamt5[f] == 1)
            binaryEncoding.set(f);
        else
            binaryEncoding.reset(f);
    }
    for (int g = 25; g <= 26; g++) { // sets bits 6-5 to sh
        if (sh[g] == 1)
            binaryEncoding.set(g);
        else
            binaryEncoding.reset(g);
    }
    binaryEncoding.reset(27); // always a 0 at bit 4
    for (int h = 28; h <= 31; h++) {
        if (Rm[h] == 1) {
            binaryEncoding.set(h);
        } else {
            binaryEncoding.reset(h);
        }
    }
    // cond, op, I, cmd, S, Rn, Rd, shamt, sh, '0', Rm
    /*
    bitset<6> begin = cat(cond, op); // combine the condition and opcode
    set_funct(); // build the funct 6-wide bitset
    bitset<12> interm0 = cat(begin, funct); // combine the first 12 bits
    
    bitset<8> midreg = cat(Rn, Rd); // combine the source and destination registers
    
    bitset<7> Src2a = cat(shamt5, sh);
    bitset<5> Src2b; // stores '0' followed by Rm
    Src2b.reset(0); // this bit is always 0
    for (int c = 1; c <=5; c++) {
        if (Rm[c] == 1)
            Src2b.set(c);
        else
            Src2b.reset(c);
    }
    bitset<12> Src2 = cat(Src2a, Src2b);
    
    bitset<20> interm1 = cat(midreg, Src2); // combine the last 20 bits
    binaryEncoding = cat(interm0, interm1); // assemble them all into the binaryEncoding member
    return;
     */
}
