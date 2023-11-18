//
//  main.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/24/23.
//

#include "finalFunctions.hpp"

using namespace std;

int main(int argc, const char * argv[]) { // HERE WE GOOOOOOOOOOOOOOO!!!...
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
    enum category {data = 0, memory, branch, label}; // define the categories of instruction
    
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
        
        // TODO: The order of this needs revision and updating so that the ends of labels are not truncated, but actual instructions do have their suffixes trimmed. The function could still confuse labels with at least conditional BL statements.
        /* figure out the condition value and opcode to encode in binary (a.k.a., the first six bits) */
        unsigned int conditionValue = checkCondition(first); // decimal integer representing the condition code
        // THE ABOVE OPERATION WILL TRIM SUFFIXES OFF OF THE INSTRUCTIONS
        unsigned int decimalOpCode = getInstructionType(first); // get operation code
        instructionType = category(decimalOpCode); // cast the opcode to an instruction type for switch statements
        
        string binaryResult, hexOutput; // strings to hold the binary concatenation and the final hex output to write
        /* I <3 C++ STL https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/ */
        map<string, int> labelMap; // an associative container to map labels to addresses properly. ONLY ONE COPY CAN EXIST
        
        /* Part IV: break up the logic by type of instruction */
        switch (instructionType) {
            case data: { // this is a data instruction
                // might still be a multiplication instruction, but these are not implemented in the prooject
                
                try { // this might not be a valid instruction.
                    string cmd = getDataCmd("PLACEHOLDER"); // store the command in a binary string
                } catch (BadInstruction()) {
                    cout << "\nERROR: The data-processing instruction encountered is not supported. For details, see the README.md or Github Wiki.\n\n";
                    return -1;
                } catch (...) {
                    cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                    return -1;
                } // If we made it this far, the instruction is indeed valid
                
                string Rd, Rn, Src2; // strings for the source, destination, and second source fields
                bool I = (currentLine.find('#') != string::npos); // check if the line operates on immediates
                bool S; // keeps track of whether this is an immediate or shifts something
                if (I) { // search for a # to check if immediates are used
                    I = true; // this is acting on an immediate
                    
                    /* Begin the list of if statements corresponding to each intruction that is valid */
                    if (first == "MOV")
                        Src2 = "";
                    
                } else {
                    I = false; // this is acting only on registers
                }
                // outFile << cond + op + I + cmd + S + Rn + Rd + Src2 << endl;
                break;
            }
            case memory: {
                // cout << cond + op + I + P + U + B + W + L + Rn + Src2 << endl;
                break;
            } // this is a memory instruction
                
            case branch: { // this is a branch instruction
                bool L = (first == "BL");
                if (L) { // this is a branch with link instruction
                    L = true;
                    outFile << conditionValue;
                } else {
                    // this is a normal branch instruction
                    L = false;
                }
            break;
            }
                
        case label: /* MAKES SOME REALLY BIG ASSUMPTIONS */
                labelMap.insert({first,lineCount*4}); // assuming that the base address is 0, each instruction is 4 bytes wide in memory
                continue; // no actual conversion or computation is required for a label.
            break;
        }
        
        try { // attempt to convert the binary encoding of the assembly instruction to hexadecimal values
            hexOutput = stringBinToHex(binaryResult); // call the function to convert the (ideally 32-bit) binary string to a hex string
        } catch (InvalidString) {
            cout << "\nThe binary reperesentation of the machine code could not be converted to hex. Terminating program.\n\n";
            return -1;
        } catch (...) {
            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
            return -1;
        }

        
    } // go until the end of the file
    /* END OF FOR LOOP */
    
    /* clean up your mess */
    inFile.close();
    inFile.clear();
    outFile.close();
    outFile.clear();
    return 0; // we did it :D
}
