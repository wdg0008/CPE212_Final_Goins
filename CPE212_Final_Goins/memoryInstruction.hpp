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
    bool P;
    bool U;
    bool B;
    bool W;
    bool L;
protected:
    bitset<6> funct; // a bitset to contain the above six bools
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
    
    void build_funct();
    // assembles the six bools into the 6-wide bitstream for future use
    // This will probably reference a more generic bool-to-bitstream function
    // A function that can add bits from bools to a bitstream is also going to be useful
    
    void accede(Instruction parent);
    // virtual function will copy all the parent data to the child class
    
    void setOp();
    // sets the operation code to 01
};

#endif /* memoryInstruction_hpp */
