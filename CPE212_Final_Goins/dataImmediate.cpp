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
    
    DataInstruction::setBinaryEncoding(); // call the parent virtual function
    for (int f = 20; f <= 24; f++) { // set bits 11-8 to rot
        if (rot[f-20] == 1) // line up the rotation bitset
            binaryEncoding.set(f);
        else
            binaryEncoding.reset(f);
    }
    for (int g = 24; g <= 31; g++) { // sets bits 7-0 to imm8
        if (imm8[g-24] == 1) // line up the imm8 bitset
            binaryEncoding.set(g);
        else
            binaryEncoding.reset(g);
    }
    return;
}
