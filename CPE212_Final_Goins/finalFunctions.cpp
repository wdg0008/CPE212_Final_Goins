//
//  finalFunctions.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/25/23.
//

#include "finalFunctions.hpp"

using namespace std;

bool openInput(ifstream& input, string& path) { // open the input file
    try { // attempt to open the input file
        string::size_type size = path.length();
        if (size < 3)
            throw InvalidSize(); // too small to be <X>.s
        string extension = path.substr((size-2), 2); // get the last two characters of the file path
        if (extension != ".s")
            throw InvalidExtension();
        input.open(path.c_str()); // attempt to open the input file
        if (input.fail()) { // deal with potential failure
            input.close();
            input.clear(); // clean up the mess
            throw FailedOpening();
        } else {
            return 1; // it worked as intended
        }
    } catch (InvalidSize) {
        cout << "\nERROR: The input file path is too short.\n\n";
        return 0;
    } catch (InvalidExtension) {
        cout << "\nERROR: The input file path does not have the required extension.\n";
        cout << "Proper usage: ./assemlber <input.s> <output.asm> \n\n";
        return 0;
    } catch (bad_alloc) {
        cout << "\nERROR: The input file could not open due to insufficient memory.\n\n";
        return 0;
    } catch (FailedOpening) {
        cout << "\nERROR: The input file failed to open.\n\n";
        return 0; // game over, man
    } catch (...) {
        cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
        return 0;
    }
}

bool openOutput(ofstream& output, string& path) { // opens output file stream with error checks
    try { // attempt to open the input file
        string::size_type size = path.length();
        if (size < 5)
            throw InvalidSize(); // too small to be <X>.s
        string extension = path.substr((size-4), 4); // get the last two characters of the file path
        if (extension != ".asm")
            throw InvalidExtension();
        output.open(path.c_str()); // attempt to open the input file
        if (output.fail()) { // deal with potential failure
            output.close();
            output.clear(); // clean up the mess
            throw FailedOpening();
        } else {
            return 1; // it worked as intended
        }
    } catch (InvalidSize) {
        cout << "\nERROR: The output file path is too short.\n\n";
        return 0;
    } catch (InvalidExtension) {
        cout << "\nERROR: The output file path does not have the required extension.\n";
        cout << "Proper usage: ./assemlber <input.s> <output.asm> \n\n";
        return 0;
    } catch (bad_alloc) {
        cout << "\nERROR: The output file failed to open due to insufficient memory.\n\n";
        return 0;
    } catch (FailedOpening) {
        cout << "\nERROR: The input file failed to open.\n\n";
        return 0; // game over, man
    } 
    catch (...) {
        cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
        return 0;
    }
}

unsigned int const checkCondition(string& instruction) { //
    /* Gets the last part of the instruction to determine if there is a condition suffix.
     Returns the binary encoding of the instruction. */
    const int count = 14;
    if (instruction.size() == 1) // this is an unconditional branch
        return 14; // the default condition AL is #15
    if (instruction.size() > 5)
        return 69; // this must be a label, so don't analyze it further or truncate it.
    string ending = instruction.substr((instruction.size()-2),2); // get the suffix at the end of the instruction
    string suffixes[count] = {"EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE"};
    
    for (int index = 0; index < count && suffixes[index] != ending; index++) { // check for presence of each suffix
        if (ending == suffixes[index]) {
            instruction = instruction.substr(0,3); // discard the suffix information to make subsequent processing simpler
            return index; // if the last two characters are exactly one of the suffixes, return that.
        }
    }
    return 14; // if no suffix was present, assume the AL suffix for constant execution.
}

unsigned int getInstructionType(string excerpt) {
    string data[10] = {"MOV", "LSL", "LSR", "ASR", "ROR", "ADD", "SUB", "AND", "ORR", "CMP"}; // data-processing instructions
    for (int i = 0; i < 10; i++) { // if the instruction is any of those in the array, it is data-processing.
        if (excerpt == data[i])
            return 0; // the op code in decimal
    }
    if (excerpt == "LDR" || excerpt == "STR")
        return 1; // the op code for memory in decimal
    else if (excerpt == "B" || excerpt == "BL")
        return 2; // the op code for branching in decimal
    else
        return 3; // this signifies a label
}

unsigned int readRegister(string reg) { // THROWS InvalidString(); it could be anything from 0-15, or written as "PC" or "LR"
    if (reg == "PC")
        return 15;
    else if (reg == "LR")
        return 14;
    else if (reg == "SP")
        return 13;
    else {
        string num = reg.substr(1,reg.length()-1); // grab all characters after the first one, which will be 'R'
        unsigned int result = stoi(num);
        if (result <= 15)
            return (result); // return the string converted to an integer
        else // wow. Xcode's linting saved me from accidentally using || to check for positive on unsigned ints
            throw InvalidString(); // there are only 16 registers (0-15) in ARM32v7 architectures
    }
}

int readImmediate(string imm) { // TODO: consider adding an error to check if the whole string was just '#' and avoid length <= 0
    return stoi(imm.substr(1, (imm.length()-1) ) ); // calls stoi to extract an int from the string, beginning at 2nd char
}


string getDataCmd(string instruction) {
    if (instruction == "ADD")
        return "0100";
    else if (instruction == "SUB")
        return "0010";
    else if (instruction == "AND")
        return "";
    else if (instruction == "ORR")
        return "";
    else if (instruction == "CMP")
        return "";
    else if (instruction == "MOV" || instruction == "LSL" || instruction == "LSR" || instruction == "ASR" || instruction == "ROR")
        return "1101";
    else
        throw (BadInstruction());
}

string snatch(string sourceLine) { // TODO: make this use vectors or something to split up each part of the line, not just the first
    string result = ""; // loop until whitespace, adding to the substring
    for (int i = 0; (i < sourceLine.length()) && (sourceLine[i] != '\t') && (sourceLine[i] != '\n') && (sourceLine[i] != ' '); i++) {
        result = result + sourceLine[i]; // concatenate the character to the string
    }
    return result;
}

string intToBinaryString(int decimalValue) { // steal code from prior project for this
    int power = -1;
    do {
        power++; // increase the power
    } while (pow(2,power) < decimalValue); // NOTE: MIGHT NEED TO BE <=
    string binaryString;
    binaryString.resize(power+1); // set the string to hold power+1 digits, the maximum it could require
    for (int i = 0; i < power; i++) {
        binaryString[power-i] = decimalValue % 2; // count down from
        decimalValue /= 2; // this should oughta work as long as no weird truncation happens
    }
    
    return binaryString;
}

string stringBinToHex(string binaryString) {
    int adjustment = 4 - ((binaryString.length()) % 4); // calculate how many zeros need to be added to align it properly
    string binaryAligned = "";
    if (adjustment == 0)
        binaryAligned = binaryString; // its length is already an integer multiple of 4
    else // this is really a failsafe; in theory, all of the strings should be 32 bits once put together.
        binaryAligned = string(adjustment,'0') + binaryString; // prepend the appropriate number of zeros
    
    /* The following section loops through the aligned binary four bits at a time, then assigns hex by comparison.
    The substring math is going to look very strange and be hard to debug. Prepare yourself. */
    
    string hexString = ""; // the string that will have each of the hex values and be returned
    
    string::size_type repetitions = (binaryAligned.length()) / 4; // figure out how many hex values to expect
    for (int count = 0; count < repetitions; count++) { // loop through each 4-bit chunk
        string smol = binaryAligned.substr(4*count,4); // grab four bits at a time, starting at four times the loop count
        /* The if statements below are essentially creating the table I look at to convert, since actual math is hard */
        if (smol == "0000") // this should really be a case statement, but C++ dynamic strings do not work like that
            hexString = hexString + '0';
        else if (smol == "0001")
            hexString = hexString + '1';
        else if (smol == "0010")
            hexString = hexString + '2';
        else if (smol == "0011")
            hexString = hexString + '3';
        else if (smol == "0100")
            hexString = hexString + '4';
        else if (smol == "0101")
            hexString = hexString + '5';
        else if (smol == "0110")
            hexString = hexString + '6';
        else if (smol == "0111")
            hexString = hexString + '7';
        else if (smol == "1000")
            hexString = hexString + '8';
        else if (smol == "1001")
            hexString = hexString + '9';
        else if (smol == "1010")
            hexString = hexString + 'A';
        else if (smol == "1011")
            hexString = hexString + 'B';
        else if (smol == "1100")
            hexString = hexString + 'C';
        else if (smol == "1101")
            hexString = hexString + 'D';
        else if (smol == "1110")
            hexString = hexString + 'E';
        else if (smol == "1111")
            hexString = hexString + 'F';
        else
            throw InvalidString();
    }
    return hexString;
}
