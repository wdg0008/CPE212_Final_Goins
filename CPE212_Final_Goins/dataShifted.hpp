//
//  dataShifted.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef dataShifted_hpp
#define dataShifted_hpp

#include "dataInstruction.hpp"

class DataShifted: public DataInstruction {
private:
    bitset<4> Rs; // register holding amount to shift the value by
    // LITERAL '0' PRESENT AT INDEX 7
    bitset<2> sh; // two bits specifying what method of shift to use
    // LITERAL '1' PRESENT AT INDEX 5
    bitset<4> Rm; // second source register
public:
    void set_Rs(string& info);
    // sets the index of the shift register to its binary value
    // this register holds the amount to shift others by
    // will need to strip off 'R' and any commas
    // will be a wrapper for lots of bitset functionality
    
    void set_sh(string& info);
    // sets the shift mode for the instruction
    
    void set_Rm(string& info);
    // set the index of the destination register
    // will need to strip off 'R' and any commas
    // will be a wrapper for lots of bitset functionality
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual function
    // This will return, in binary, the following fields in the following order:
    // cond, op, I, cmd, S, Rn, Rd, Rs, '0', sh, '1', Rm
};

#endif /* dataShifted_hpp */
