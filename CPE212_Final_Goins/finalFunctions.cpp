//
//  finalFunctions.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/25/23.
//

#include "finalFunctions.hpp"

using namespace std;

bool openInput(ifstream input, string path) { // open the input file
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

bool openOutput(ofstream output, string path) { // opens output file stream with error checks
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
    int suffixDec = 15; // default condition AL is number 15
    string suffixes[count] = {"EQ", "NE", "CS", "CC", "MI", "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT", "LE"};
    
    for (int index = 0; index < count && suffixes[index] != ending; index++) { // check for presence of each suffix
        if (ending == suffixes[index]) // if the last two characters are exactly one of the suffixes, return that.
            return index;
    }
    return 14; // if no suffix was present, assime the AL suffix for constant execution.
}
