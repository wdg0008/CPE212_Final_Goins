//
//  memoryImmediate.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef memoryImmediate_hpp
#define memoryImmediate_hpp

#include "memoryInstruction.hpp"

class MemoryImmediate: public MemoryInstruction {
private:
    bitset<12> imm12; // immediate value to store or load
public:
    void set_imm12(string& info);
    // converts the string to a bitset
    // will need to strip off any '#' character or commas
    // could be in either hex or decimal
    // in hex, a reverse lookup table can be used to iterate through the string
    // in decimal, it will have to be converted to binary (using bitset to_string, probably)
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual function
    // This will return, in binary, the following fields in the following order:
    // cond, op, funct, Rn, Rd, imm12
};

#endif /* memoryImmediate_hpp */
