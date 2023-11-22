//
//  branchInstruction.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef branchInstruction_hpp
#define branchInstruction_hpp

#include "instruction.hpp"

class BranchInstruction: public Instruction {
private:
    // LITERAL '1' PRESENT AT INDEX 25
    bool L; // true if the instruction is a branch with link
    bitset<24> imm24; // holds the addreess to branch to in binary
public:
    BranchInstruction();
    // Default constructor with all the values initialized to zero (except op)
    
    bool isLink(string& instruction);
    // sets L based on whether the instruction is a branch with link
    // returns the value that L is set to (might change this later)
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual function
    // This will return, in binary, the following fields in the following order:
    // cond, op, '1', L, imm24
    
    void setOp();
    // sets the operation code to 10
};

#endif /* branchInstruction_hpp */
