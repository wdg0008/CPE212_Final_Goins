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
    try { // attempt to open the input file
        inFile.open(inPath.c_str());
        if (inFile.fail())
            throw -1;
    } catch (int) {
        cout << "\nERROR: The input file failed to open.\n\n";
        return -1; // game over, man
    }
    
    try { // attempt to open the output file
        outFile.open(outPath.c_str());
        if (outFile.fail())
            throw -1;
    } catch (int) {
        cout << "\nERROR: The output file failed to open.\n\n";
        return -1; // game over, man
    }
    
    /* Part II: Scaffolding for the line-by-line loop */
    string currentLine; // define the line that is being analyzed on each iteration
    bool isEmpty = true; // define a flag for empty files
    enum category {data, memory, branch}; // define the categories of instruction
    enum cond {EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL}; // enumerate condition list
    
    /* Part III: The loop logic */
    do {
        getline(inFile, currentLine, ';'); // read each line of the input file
        if (currentLine == "")
            continue; // skip to the next iteration
        category instructionType;
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
        
    } while (!inFile.fail() && !inFile.eof());
    getline(cin, currentLine, ';');
    return 0;
}
