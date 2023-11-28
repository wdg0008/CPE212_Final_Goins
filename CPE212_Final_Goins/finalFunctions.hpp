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
#include <stdexcept> // built-in exceptions

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

unsigned int getInstructionType(string excerpt);
// return the op code for the instruction or decide it is a label
// does NOT change the string passed to it as an argument

unsigned int readRegister(string reg);
// get the decimal index value of the register
// wraps a call to scrubString with code to detect special register names

string getDataCmd(string instruction); // get the binary cmd value for the data-processing instruction as a string

string snatch(string sourceLine); // riff off of extraction for a string input

string intToBinaryString(int decimalValue);

string stringBinToHex(string binaryString);

bool findStringChar(string& info, char target); // returns true if character present in string

bool stringInArray(const string& item, const string searchSpace[], unsigned int spaceSize);
// returns true if the string matches one of the elements in the array of specified size

int scrubString(string& info);
// removes the first character of the string and any commas at the end
// converts the cleaned string into an integer

int grabIntAfterChar(stringstream& somestream, char predecessor);
// extracts an integer from the stringstream after ignoring until the specified character

unsigned int getNextReg(stringstream& somestream);
// returns the next register in the stringstream
// includes funcitonality to detect the special register names
#endif /* finalFunctions_hpp */
