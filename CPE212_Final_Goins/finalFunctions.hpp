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

#endif /* finalFunctions_hpp */
