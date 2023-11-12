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
    if (instruction.size() <= 2)
        return 14; // the default condition AL is #15
    string ending = instruction.substr((instruction.size()-2),2); // get the suffix at the end of the instruction
    string suffixes[count] = {"EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE"};
    
    for (int index = 0; index < count && suffixes[index] != ending; index++) { // check for presence of each suffix
        if (ending == suffixes[index]) // if the last two characters are exactly one of the suffixes, return that.
            return index;
    }
    return 14; // if no suffix was present, assime the AL suffix for constant execution.
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

unsigned int readRegister(string reg) { // it could be anything from 0-15, or written as "PC" or "LR"
    if (reg == "PC")
        return 15;
    else if (reg == "LR")
        return 14;
    else if (reg == "SP")
        return 13;
    else {
        string num;
        if (reg.length() == 2) // in the form of RX
            num = reg.substr(1,1); // grab one character after the first one
        else // in the form of RXX
            num = reg.substr(1,2); // grab the last two characters after the first one
        return (stoi(num)); // return the string converted to an integer
    }
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

string snatch(string sourceLine) {
    string result = ""; // loop until whitespace, adding to the substring
    for (int i = 0; (i < sourceLine.length()) && (sourceLine[i] != '\t') && (sourceLine[i] != '\n') && (sourceLine[i] != ' '); i++) {
        result = result + sourceLine[i]; // concatenate the character to the string
    }
    return result;
}
