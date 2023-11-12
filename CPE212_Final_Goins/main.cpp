//
//  main.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/24/23.
//

#include "finalFunctions.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 3) { // check the basic form of the program call
        cout << "\nIncorrect number of arguments. Usage:\n./assembler <input.s> <output.asm>\n\n";
        return -1;
    }
    /* Part I: Arguments and File Manipulation */
    // declare file variables
    string inPath = argv[1];
    string outPath = argv[2];
    ifstream inFile;
    ofstream outFile;
    
    // open files
    bool validInput = openInput(inFile, inPath); // call the input-opening function
    bool validOutput = openOutput(outFile, outPath); // call the output-opening function
    if (!validInput || !validOutput)
        return -1; // game over, bro.
    
    /* Part II: Scaffolding for the line-by-line loop */
    string currentLine; // define the line that is being analyzed on each iteration
    bool isEmpty = true; // define a flag for empty files
    enum category {data = 1, memory, branch, label}; // define the categories of instruction
    
    /* Part III: The loop logic */
    for (int lineCount = 0; !inFile.fail() && !inFile.eof(); lineCount++) { // counter starts at 0, x4 for the address
        getline(inFile, currentLine, '\n'); // read each line of the input file
        
        /* check for empty lines that don't do anything */
        if (currentLine == "")
            continue; // skip to the next iteration
        
        /* Get the first word of the line to see if it is a label or what type of instruction it is */
        category instructionType; // define an enum for which type of instruction it is
        string first;
        first = snatch(currentLine); // store the first part of the line (the instruction or a label)
        
        unsigned int decimalOpCode = getInstructionType(first); // get operation code
        instructionType = category(decimalOpCode); // cast the opcode to an instruction type for switch statements
        
        /* figure out the condition value to encode in binary */
        unsigned int conditionValue = checkCondition(currentLine); // deciaml integer representing the condition code
        
        /* Part IV: break up the logic by type of instruction */
        switch (instructionType) {
        case data: // this is a data instruction
                // might still be a multiplication instruction, but these are not implemented in the prooject
                
                try { // this might not be a valid instruction.
                    string cmd = getDataCmd(first); // store the command in a binary string
                } catch (BadInstruction()) {
                    cout << "\nThe data-processing instruction encountered is not supported. For details, see the README.md or Github Wiki.\n\n";
                    return -1;
                } catch (...) {
                    cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                    return -1;
                }
                
                bool I, S; // keeps track of whether this is an immediate or shifts something
                if (currentLine.find('#') != string::npos) { // search for a # to check if immediates are used
                    I = true; // this is
                } else {
                    I = false;
                }
                // outFile << cond + op + I + cmd + S + Rn + Rd + Src2 << endl;
            break;
        case memory: // this is a memory instruction
                // cout << cond + op + I + P + U + B + W + L + Rn + Src2 << endl;
            break;
        case branch: // this is a branch instruction
                bool L;
                if (first == "BL") {
                    L = true;
                    // this is a branch with link
                } else {
                    // this is a normal branch instruction
                    L = false;
                }
            break;
        case label:
                // need to store the address to come back to. Queue? List? Array?
            break;
        }
        
    } // go until the end of the file
    
    /* clean up your mess */
    inFile.close();
    inFile.clear();
    outFile.close();
    outFile.clear();
    return 0; // we did it :D
}
