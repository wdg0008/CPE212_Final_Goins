//
//  finalFunctions.hpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/25/23.
//

#ifndef finalFunctions_hpp
#define finalFunctions_hpp

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <new>
#include <cmath>
#include <map>
#include <bitset>
#include <sstream>

using namespace std;

/* The following class definitions are empty error handling classes to help me read code */
class InvalidSize {};
class InvalidExtension {};
class FailedOpening {};
class BadInstruction {};
class InvalidString {};

bool openInput(ifstream& input, string& path); // opens input file stream with error checks

bool openOutput(ofstream& output, string& path); // opens output file stream with error checks

unsigned int const checkCondition(string& instruction); // check the end of the instruction string for one of the conditions

unsigned int getInstructionType(string excerpt); // return the op code for the instruction or decide it is a label

unsigned int readRegister(string reg); // get the decimal index value of the register

int readImmediate(string imm); // get the immediate out of the instruction

string getDataCmd(string instruction); // get the binary cmd value for the data-processing instruction as a string

string snatch(string sourceLine); // riff off of extraction for a string input

string intToBinaryString(int decimalValue);

string stringBinToHex(string binaryString);

template <size_t X, size_t Y> // not exactly sure if this is the best option, see https://stackoverflow.com/questions/3061721/concatenate-boostdynamic-bitset-or-stdbitset
bitset<X +Y> cat(const bitset<X>& b1, const bitset<Y>& b2); // concatenate two bitsets into a single bitset

bool findStringChar(string& info, char target); // returns true if character present in string

bool stringInArray(const string& item, const string searchSpace[], unsigned int spaceSize);
// returns true if the string matches one of the elements in the array of specified size

int scrubString(string& info);
// removes the first character of the string and any commas at the end
// converts the cleaned string into an integer

#endif /* finalFunctions_hpp */
