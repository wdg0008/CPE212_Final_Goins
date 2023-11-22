//
//  dataImmediate.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef dataImmediate_hpp
#define dataImmediate_hpp

#include "dataInstruction.hpp"

class DataImmediate: public DataInstruction {
private:
    bitset<4> rot; // 4 bit amount to rotate immediate value
    bitset<8> imm8; // immediate value encoded in 8 bits
public:
    DataImmediate();
    // sets the immedaite bit to true and op to 0
    
    void set_imm8(string& info);
    // Stores the actual immediate value into the private member
    // Will need to remove the prepending "#" and any commas
    // Will definitely also be a wrapper for bitset functionality
    // Sets the rotate bit based on whether the value can fit in 8 bits or not (i.e.  |x| < 128)
    // This will end up being a complete and total pain to get right if it only rotates right...
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual funciton
    // This will return, in binary, the following fields in the following order:
    // cond, op, I, cmd, S, Rn, Rd, rot, imm8
};

#endif /* dataImmediate_hpp */
