//
//  dataRegister.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef dataRegister_hpp
#define dataRegister_hpp

#include "dataInstruction.hpp"

class DataRegister: public DataInstruction {
private:
    bitset<5> shamt5; // 5-bit shift amount
    bitset<2> sh; // 2-bit shift mode
    // ZERO IS PRESENT BY DEFAULT AT INDEX 4
    bitset<4> Rm; // second source register
public:
    DataRegister();
    // Default constructor doesn't do a whole lot, but exists to appease the compiler
    
    void set_shamt5(string& info);
    // set the amount to shift by, depending on the instruction
    // NOTE: Not really sure when this is important or useful, so will be done much later
    
    void set_sh(string& info);
    // set the sh value to switch what shift mode is used, if any
    // how the hardware interprets differences between LSL, LSR, ASR, etc.
    
    void set_Rm(string& info);
    // sets the second source register from a string extracted by main
    // Must be any of R0-R15
    
    void setBinaryEncoding();
    // Implements the grandparent pure virtual function
    // This will return, in binary, the following fields in the following order:
    // cond, op, I, cmd, S, Rn, Rd, shamt, sh, '0', Rm
    
    void accede(DataInstruction parent);
};

#endif /* dataRegister_hpp */
