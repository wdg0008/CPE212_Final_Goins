//
//  main.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/24/23.
//

#include "finalFunctions.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
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
    enum category {data, memory, branch}; // define the categories of instruction
    enum cond {EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL}; // enumerate condition list
    
    /* Part III: The loop logic */
    do {
        getline(inFile, currentLine, ';'); // read each line of the input file
        
        /* check for empty lines that don't do anything */
        if (currentLine == "")
            continue; // skip to the next iteration
        
        /* figure out the condition value to encode in binary */
        unsigned int conditionValue = checkCondition(currentLine); // deciaml integer representing the condition code
        
        /* Part IV: loop through each part of the instruction */
        switch (instructionType) {
        case data: // this is a data instruction
            // might still be a multiplication instruction
            // if
            break;
        case memory: // this is a memory instruction
            break;
        case branch: // this is a branch instruction
            break;
        }
        
    } while (!inFile.fail() && !inFile.eof()); // go until the end of the file
    
    /* clean up your mess */
    inFile.close();
    inFile.clear();
    outFile.close();
    outFile.clear();
    return 0; // we did it :D
}
