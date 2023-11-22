//
//  dataShifted.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataShifted.hpp"

void DataShifted::setBinaryEncoding() {
    // cond, op, I, cmd, S, Rn, Rd, Rs, '0', sh, '1', Rm
    bitset<6> begin = cat(cond, op); // combine the condition and opcode
    set_funct(); // build the funct 6-wide bitset
    bitset<12> interm0 = cat(begin, funct); // combine the first 12 bits
    
    bitset<8> midreg = cat(Rn, Rd); // combine the source and destination registers
    
    /* build Src2 */
    bitset<4> Src2a; // stores '0' followed by sh followed by '1'
    Src2a.reset(0); // this bit is always 0
    for (int c = 1; c <=2; c++) {
        if (sh[c] == 1)
            Src2a.set(c);
        else
            Src2a.reset(c);
    }
    Src2a.set(3);
    bitset<8> Src2b = cat(Src2a, Rm);
    bitset<12> Src2 = cat(Rs, Src2b);
    
    bitset<20> interm1 = cat(midreg, Src2); // combine the last 20 bits
    binaryEncoding = cat(interm0, interm1); // assemble them all into the binaryEncoding member
    return;
}
