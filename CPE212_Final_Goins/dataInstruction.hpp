//
//  dataInstruction.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef dataInstruction_hpp
#define dataInstruction_hpp

#include "instruction.hpp"

class DataInstruction: public Instruction {
protected:
    bool I; // immediate bit (true if operating on an immediate)
    bitset<4> cmd; // four bits for command
    bool S; // shift bit (true if shifting the value)
    bitset<6> funct; // a bitset to contain I, cmd, and S
    bitset<4> Rd; // destination register index
    bitset<4> Rn; // source register index
public:
    DataInstruction();
    // default constructor sets op to 0
    
    void set_S(bool value);
    // Sets the shift bit depending on whether the instruction shifts the value
    // Works on LSL, LSR, ASR, and ROR (RRX is NOT implemented in this project)
    
    void set_I(bool value);
    // Sets the immediate bit depending on whether or not an operand is an immediate
    // This should be fairly easy to check based on the presence of '#'
    
    void set_cmd(string& info);
    // Sets the cmd value corresponding to which instruction is being executed.
    // Each instruction has a unique cmd value, except for moves, shifts, and rotates
    
    void set_funct();
    // builds the funct bitset from I, cmd, and S
    
    void setRn(unsigned int index);
    // sets the source register to the value of the index
    
    void setRd(unsigned int index);
    // sets the source register to the value of the index
};
#endif /* dataInstruction_hpp */
