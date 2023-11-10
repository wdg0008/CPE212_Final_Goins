//
//  finalFunctions.cpp
//  CPE212_Final_Goins
//
//  Created by William Goins V on 10/25/23.
//

#include "finalFunctions.hpp"

using namespace std;

template <typename FileType> // template function to open input and output files
bool openFile(FileType file, string path) {
    try { // attempt to open the input file
        file.open(path.c_str());
        if (file.fail()) {
            file.close();
            file.clear();
            throw -1;
        } else {
            return 1;
        }
    } catch (int) {
        cout << "\nERROR: The input file failed to open.\n\n";
        return 0; // game over, man
    }
}
