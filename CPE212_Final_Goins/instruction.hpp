//
//  instruction.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 11/19/23.
//

#ifndef instruction_hpp
#define instruction_hpp

#include "finalFunctions.hpp" // for reusable functions that need to exist outside classes
// also has the side benefit of condensing most of my #include statements to one file

using namespace std;

class Instruction { // base calss for all instruction types
protected: // the whole point is to inherit these shared members
    bitset<4> cond; // four bit condition code
    bitset<2> op; // two bit op code
    bitset<32> binaryEncoding; // 32 bits for the total instruction
public:
    /* Constructor Functions */
    Instruction(); // default constructor
    Instruction(bitset<4> c, bitset<2> o); // build from a known condition and opcode
    
    /* Transofrmer Functions */
    void setCondition(unsigned int value);
    // Sets the condition of the instruction based on the string passed to it
    // Will trim off the last two characters of a string if they signify a condition
    
    bitset<4> getCondition();
    // returns the condition value asosciated with the instruction as a 4-wide bitset
    
    virtual void setBinaryEncoding() = 0; // generate encoding with polymorphism???
    // This function, implemented by children, concatenates the bitsets together
    // The 32-bit instruction should then be able to encode into hex very easily
    
    bitset<32> getInstructionWord();
    // returns the literal 32-wide bitset containing the binary encoding of the value
    // should not really be necessary, but it's here just in case
    
    unsigned long getDecimalEncoding();
    // This function will return an integer representation of the equivalent binary encoding
    // In reality, it is a glorified wrapper for information stored in the 32-bitset
    
    string getHexEncoding();
    // This is where all the magic happens. The string it returns is the equivalent hex value.
    // It works by comparing each group of four bits to their hexadecimal equivalent
    // The returned string should be the final output that gets printed to the file
    
    // virtual void accede() = 0;
    // This is a pure virtual function that children will use to copy parent data
    // Allows instantiating the parent class and passing data to the appropriate child as it reads
};
#endif /* instruction_hpp */
