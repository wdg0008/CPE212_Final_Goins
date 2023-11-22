//
//  memoryRegister.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef memoryRegister_hpp
#define memoryRegister_hpp

#include "memoryInstruction.hpp"

class MemoryRegister: public MemoryInstruction {
private:
    bitset<5> shamt5; // amount to shift value by
    bitset<2> sh; // shifting mode indicator
    // LITERAL '1' PRESENT AT INDEX 4
    bitset<4> Rm; // index of second source register
public:
    void set_shamt5(string& info);
    // set the integer amount to shift the value by
    // will use lots of bitset functionality to convert decimal
    
    void set_sh(string& info);
    // set the shifting mode to use based on what type of instruction it is
    // Not really sure what to put here, need to review the stuff in the book
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual function
    // This will return, in binary, the following fields in the following order:
    // cond, op, funct, Rn, Rd, shamt5, sh, '1', Rm
    // Again, will need to concatenate bitsets of known lengths to 32 bits
};

#endif /* memoryRegister_hpp */
