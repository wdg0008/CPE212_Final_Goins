//
//  dataImmediate.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataImmediate.hpp"

DataImmediate::DataImmediate() {
    I = true;
    op = bitset<2>(0);
}

void DataImmediate::set_imm8(string& info) {
    int value = scrubString(info);
    if (value < 128 && value > -128) { // value fits in eight bits
        imm8 = bitset<8>(value);
        rot = bitset<4>(0); // no rotation necessary
    } else {
        imm8 = bitset<8>(value % 128); // TODO: Put real code here
    // https://alisdair.mcdiarmid.org/arm-immediate-value-encoding/
    // https://www.davespace.co.uk/arm/introduction-to-arm/immediates.html
    }
}

void DataImmediate::setBinaryEncoding() {
    // cond, op, I, cmd, S, Rn, Rd, rot, imm8
    
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
    for (int f = 20; f <= 24; f++) { // set bits 11-8 to rot
        if (rot[f] == 1)
            binaryEncoding.set(f);
        else
            binaryEncoding.reset(f);
    }
    for (int g = 24; g <= 31; g++) { // sets bits 7-0 to imm8
        if (imm8[g] == 1)
            binaryEncoding.set(g);
        else
            binaryEncoding.reset(g);
    }
    /* bitset<6> begin = cat(cond, op); // combine the condition and opcode
    set_funct(); // build the funct 6-wide bitset
    bitset<12> interm0 = cat(begin, funct); // combine the first 12 bits
    
    bitset<8> midreg = cat(Rn, Rd); // combine the source and destination registers
    
    // build Src2
    bitset<12> Src2 = cat(rot, imm8);
    bitset<20> interm1 = cat(midreg, Src2);
    binaryEncoding = cat(interm0, interm1); // assemble them all into the binaryEncoding member
    */
    return;
}
