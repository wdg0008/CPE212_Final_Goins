//
//  dataShifted.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#include "dataShifted.hpp"

DataShifted::DataShifted() {
    Rm = 0;
}

void DataShifted::setBinaryEncoding() {
    // cond, op, I, cmd, S, Rn, Rd, Rs, '0', sh, '1', Rm
    DataInstruction::setBinaryEncoding();
    binaryEncoding.reset(24);
    for (int f = 0; f <= 1; f++) {
        if (sh[f] == 1) {
            binaryEncoding.set(f+25);
        } else {
            binaryEncoding.reset(f+25);
        }
    }
    binaryEncoding.set(27);
    for (int g = 0; g <= 3; g++) {
        if (Rm[g] == 1) {
            binaryEncoding.set(g+28);
        } else {
            binaryEncoding.reset(g+28);
        }
    }
    return;
}
