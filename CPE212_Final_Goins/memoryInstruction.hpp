//
//  memoryInstruction.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef memoryInstruction_hpp
#define memoryInstruction_hpp

#include "instruction.hpp"

class MemoryInstruction: public Instruction {
private:
    bool I; // true for operations involving immediates
    bool P; // the Pre-Index bit is true for pre-index AND offset mode, but false for post-index
    bool U; // add offfset to base when true, subtract when false
    bool B; // true if loading or storing only a byte, false otherwise (ONLY FALSE FOR NOW)
    bool W; // writeback bit is true for pre-indexed mode
    bool L; // true for load instructions, false for store instrucitons
    /* The following details what bits are set for which indexing mode:
     Offset: LDR R0, [R1, R2]
     This will load R1+R2 into R0 without overwriting anyting. P is true and W is NOT
     Pre-Index: LDR R0, [R1, R2]!
     This will load R1+R2 into R0 AND overwrite R1 with R1+R2. P is true and W is true
     Post-Index: LDR R0, [R1], R2
     This will load R1 into R0 before overwriting R1 with R1+R2. P and W are BOTH FALSE
     */
protected:
    bitset<4> Rn; // the index of the source register
    bitset<4> Rd; // the index of the destination register
public:
    MemoryInstruction();
    // Default constructor sets op to 1
    
    void set_values(string& info);
    // sets the value of I based on whether an immedaite is present, shown by '#'
    // sets the value of all the other stuff, which I don't remember
    
    void set_Rn(string& info);
    // sets the index of the source register
    // Will need to remove the prepending "R" and any commas
    // Will definitely also be a wrapper for bitset functionality
    
    void set_Rd(string& info);
    // set the index of the destination register
    // will need to strip off 'R' and any commas
    // will be a wrapper for lots of bitset functionality
    
    void accede(Instruction parent);
    // virtual function will copy all the parent data to the child class
    // TODO: Evaluate this function for removal
    
    void setBinaryEncoding();
    // virtual function will set cond, op, funct, Rn, and Rd
    // Everything except Src2 is specified in this funciton, children finish it
    // just filling in a bitset
};

#endif /* memoryInstruction_hpp */
