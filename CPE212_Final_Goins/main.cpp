//
//  main.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/24/23.
//

#include "finalFunctions.hpp"
#include "instruction.hpp" // parent instruction class, followed by children and grandchildren
#include "dataImmediate.hpp"
#include "dataRegister.hpp"
#include "dataShifted.hpp"
#include "memoryImmediate.hpp"
#include "memoryRegister.hpp"
#include "branchInstruction.hpp"

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
    
    /* The following lines pertaining to cin make it check what base the value is in
     and save me lots of logical checks on what base it being read in. C++ will essentially
     figure out from the 0x prefix (or lack thereof) whether to treat the number as hex. */
    inFile.unsetf(std::ios::dec); // force inferral of decimal values
    // inFile.unsetf(std::ios::oct); // force inferral of octal values (UNUSED)
    inFile.unsetf(std::ios::hex); // force inferral of hex values
    
    /* Part II: Scaffolding for the line-by-line loop */
    enum category {data = 0, memory, branch, label}; // define the categories of instruction
    const string dataList[10] = {"MOV", "LSL", "LSR", "ASR", "ROR", "ADD", "SUB", "AND", "ORR", "CMP"};
    const string dataShifting[4] = {"LSL", "LSR", "ASR", "ROR"};
    const string instructionList[14] = {"MOV", "LSL", "LSR", "ASR", "ROR", "ADD", "SUB", "AND", "ORR", "CMP", "BL", "B", "STR", "LDR"};
    
    /* Part III: The loop logic */
    for (int lineCount = 0; !inFile.fail() && !inFile.eof(); lineCount++) { // counter starts at 0, x4 for the address
        string currentLine; // define the line that is being analyzed on each iteration, destroyed after each iteration
        getline(inFile, currentLine, '\n'); // read each line of the input file
        
        /* check for empty lines that don't do anything */
        if (currentLine == "") {
            lineCount--;
            continue; // skip to the next iteration
        }
        
        stringstream line; // stream to make the string act like the input file without changing the actual input file
        /* force the stringstream to check for decimal or hex values every time it extracts */
        line.unsetf(std::ios::dec); // force inferral of decimal values
        // inFile.unsetf(std::ios::oct); // force inferral of octal values (UNUSED)
        line.unsetf(std::ios::hex); // force inferral of hex values
        
        line << currentLine; // store the current line into a seperate stream
        
        /* Get the first word of the line to see if it is a label or type of instruction */
        string first;
        line >> first; // store the first part of the line (the instruction or a label)
        
        category instructionType; // define an enum for which type of instruction it is
        unsigned int decimalOpCode = getInstructionType(first); // get operation code
        instructionType = category(decimalOpCode); // cast the opcode to an instruction type for switch statements
        
        /* figure out the condition value and opcode to encode in binary (a.k.a., the first six bits) */
        unsigned int conditionValue = checkCondition(first); // decimal integer representing the condition code
        // THE ABOVE OPERATION WILL TRIM SUFFIXES OFF OF THE INSTRUCTIONS
        // This operation currently CANNOT recognize the 'S' suffix for setting condition flags
        
        /* I <3 C++ STL https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/ */
        map<string, int> labelMap; // an associative container to map labels to addresses properly.
        // ONLY ONE COPY OF A LABEL CAN EXIST AT ANY POINT IN TIME
        
        /* Part IV: break up the logic by type of instruction */
        switch (instructionType) {
            case data: { // this is a data instruction
                // might still be a multiplication instruction, but these are not implemented in the project
                cout << "Processing data instruction: " << first << endl; // debug to validate sorting
                string Rd, Rn; // strings for the source and destination fields
                line >> Rd; // read in the destination register (present for ALL data instructions)
                
                if (first == "MOV") { // MOV requires special handling
                    string dummy = "R0"; // declared seperately to appease the compiler
                    string origin = "0"; // more strange side effects of string arguments
                    if (findStringChar(currentLine, '#')) {
                        DataImmediate movImm; // object to encapsulate a MOV instruction with an imm
                        string imm; // read in an immediate value to MOV
                        line >> imm;
                        try {
                            movImm.set_Rd(Rd);
                            movImm.setCondition(conditionValue);
                            movImm.set_Rn(dummy); // always set to 0 for MOV
                            movImm.set_imm8(imm); // store the immediate after adjusting it for rot
                            movImm.set_cmd(first); // should be set to MOV
                            movImm.set_S(false);
                            movImm.setBinaryEncoding(); // virtual function
                            outFile << movImm.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                    } else {
                        DataRegister movReg; // object to encapsulate a MOV instruction on registers
                        string Rm;
                        line >> Rm; // get the register for Src2
                        try {
                            movReg.set_Rd(Rd);
                            movReg.setCondition(conditionValue);
                            movReg.set_Rn(Rn);
                            movReg.set_Rm(Rm);
                            movReg.set_shamt5(origin);
                            movReg.set_cmd(first);
                            movReg.set_S(false);
                            movReg.setBinaryEncoding(); // virtual function
                            outFile << movReg.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            // this means a register was invalid
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                    }
                } else if (stringInArray(first, dataShifting, 4)) { // guaranteed to not be MOV from here
                    // This will shift the register, so it is either an immediate-shifter or register-shifted register
                    // Instruction is one of: LSL, LSR, ASR, ROR, RRX, MOV
                    line >> Rn; // source register exists for all non-MOV data-processing instrucitons
                    if (findStringChar(currentLine, '#')) {
                        // This is an immediate-shifter
                        DataRegister regInst;
                        try {
                            string Rm, imm, lit0 = "R0";
                            line >> Rm;
                            line >> imm; // TODO: Consider modulo logic for shifts >= 32 bits
                            regInst.setCondition(conditionValue);
                            regInst.set_Rd(Rd);
                            regInst.set_Rn(lit0); // source register is 0 for a shift operating on one register and an immediate
                            regInst.set_Rm(Rm);
                            regInst.set_shamt5(imm); // the immediate value at the end is the amount to shift by
                            regInst.set_cmd(first);
                            regInst.set_S(false);
                            regInst.setBinaryEncoding(); // virtual function
                            outFile << regInst.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            // this means a register was invalid
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                    } else {
                        // This is a register-shifting register operation
                        DataShifted shiftInst;
                        try {
                            string Rm, Rs,  lit0 = "R0";
                            line >> Rm; // source register in Src2
                            line >> Rs; // register containing amount to shift by
                            shiftInst.setCondition(conditionValue);
                            shiftInst.set_cmd(first);
                            shiftInst.set_S(false);
                            shiftInst.set_Rn(lit0); // source register is always 0
                            shiftInst.set_Rd(Rd);
                            shiftInst.set_Rs(Rs);
                            shiftInst.set_sh(first);
                            shiftInst.set_Rm(Rm);
                            shiftInst.setBinaryEncoding();
                            outFile << shiftInst.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            // this means a register was invalid
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                    }
                } else {
                    // This will NOT shift the register, so it is either operating on immediates or two registers with shamt5 = 0
                    // Instruction is one of: AND, EOR, ORR, SUB, NOT, ADD, ORR
                    if (findStringChar(currentLine, '#')) {
                        // This is operating directly on unshifted immediates
                        DataImmediate immInst;
                        try {
                            string imm;
                            line >> imm;
                            line >> Rd;
                            line >> Rn;
                            immInst.setCondition(conditionValue);
                            immInst.set_cmd(first);
                            immInst.set_S(false);
                            immInst.set_Rn(Rn);
                            immInst.set_Rd(Rd);
                            immInst.set_imm8(imm); // TODO: Finish and impelement the rotation stuffs
                            immInst.setBinaryEncoding();
                            outFile << immInst.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            // this means a register was invalid
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                        immInst.set_cmd(first);
                        string immediate;
                        line >> immediate;
                        immInst.set_imm8(immediate);
                    } else {
                        // This is operating on two nonshifting registers
                        string Rm;
                        line >> Rm; // read in the second source register
                        string lit0 = "#0";
                        DataRegister regInst;
                        try {
                            regInst.set_Rd(Rd);
                            regInst.setCondition(conditionValue);
                            regInst.set_Rn(Rn);
                            regInst.set_Rm(Rm);
                            regInst.set_shamt5(lit0); // no shifting here
                            regInst.set_cmd(first);
                            regInst.set_S(false);
                            regInst.setBinaryEncoding(); // virtual function
                            outFile << regInst.getHexEncoding() << endl;
                        } catch (InvalidString) {
                            // this means a register was invalid
                            cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                            cout << currentLine << endl;
                            cout << "Terminating program.\n\n";
                            return -1;
                        } catch (...) {
                            cout << "\nERROR: Unknown error encountered. Terminating program.\n\n";
                            return -1;
                        }
                    }
                }
                break;
            }
            case memory: {
                // cout << cond + op + I + P + U + B + W + L + Rn + Src2 << endl;
                cout << "Processing memory instruction: " << first << endl; // debug to validate sorting
                string Rn, Rd;
                line >> Rd;
                if (findStringChar(currentLine, '#')) {
                    // ths is an immediate-operating memory instruction
                    MemoryImmediate immMem;
                    string imm;
                    try {
                        immMem.set_values(currentLine);
                        immMem.setCondition(conditionValue);
                        immMem.set_Rn(Rn); // sets the source register
                        line.ignore(INT8_MAX, '[');
                        line >> Rd;
                        if (findStringChar(Rd, ']'))
                            Rd.substr(0,Rd.length()-1); // discard the right brace if present
                        immMem.set_Rd(Rd); // sets the destination register
                        line >> imm;
                        if (findStringChar(imm, ']'))
                            imm.substr(0,imm.length()-1); // discard the right brace if present
                        immMem.set_imm12(imm);
                        immMem.setBinaryEncoding();
                        outFile << immMem.getHexEncoding() << endl;
                    } catch (InvalidString) {
                        // bad register
                        cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                        cout << currentLine << endl;
                        cout << "Terminating program.\n\n";
                        return -1;
                    } catch (...) {
                        // uh oh
                        return -1;
                    }
                } else {
                    // this is a register-operating memory instruction
                    MemoryRegister regMem;
                    string Rm;
                    try {
                        regMem.set_values(currentLine);
                        regMem.setCondition(conditionValue);
                        regMem.set_Rn(Rn);
                        line >> Rd;
                        if (findStringChar(Rd, ']'))
                            Rd.substr(0,Rd.length()-1); // discard the right brace if present
                        regMem.set_Rd(Rd); // sets the destination register
                        line >> Rm;
                        if (findStringChar(Rm, ']'))
                            Rm.substr(0,Rm.length()-1); // discard the right brace if present
                        regMem.set_Rm(Rm);
                        regMem.setBinaryEncoding();
                        outFile << regMem.getHexEncoding() << endl;
                    } catch (InvalidString) {
                        // code
                        cout << "\nERROR: The following instruction contained instructions referencing invalid registers:\n";
                        cout << currentLine << endl;
                        cout << "Terminating program.\n\n";
                        return -1;
                    } catch (...) {
                        // uh oh
                        return -1;
                    }
                    
                }
                break;
            } // this is a memory instruction
                
            case branch: { // this is a branch instruction
                cout << "Processing branch instruction: " << first << endl; // debug to validate sorting
                BranchInstruction bInst; // no weird error handling required
                bInst.setCondition(conditionValue);
                string destination;
                line >> destination; // extract the destination label from the stringstream containing the current line
                bool L = bInst.isLink(first); // set the link bit in the object and return it
                (L) ? (cout << "Branch instruction links.\n") : (cout << "Branch instruction does not link.");
                bInst.set_imm24(labelMap, destination); // set imm24 to the address of the destination in the map
                bInst.setBinaryEncoding();
                outFile << bInst.getHexEncoding() << endl;
            break;
            }
                
        case label: /* MAKES SOME REALLY BIG ASSUMPTIONS */
                cout << "Adding label to map: " << first << endl; // debug to validate sorting
                labelMap.insert({first,lineCount*4}); // assuming that the base address is 0, each instruction is 4 bytes wide in memory
                continue; // no actual conversion or computation is required for a label.
            break;
        default: // don't know how this would happen, but just in case
                cout << "\nERROR: The instruction could not be recognized and categorized by the assembler: " << first << endl;
                cout << "Program terminating...\n\n";
                break;
        }
        line.clear(); // empty out the stringstream for good measure
    } // go until the end of the file
    /* END OF FOR LOOP */
    
    /* clean up your mess */
    inFile.close();
    inFile.clear();
    outFile.close();
    outFile.clear();
    return 0; // we did it :D
}
