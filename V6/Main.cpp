#include <iostream>
#include <fstream>

#include "Memory.h"

using namespace std;

int main() {

    // Open file containing reference string
    fstream inputFile;
    inputFile.open("ReferenceString1.txt");

    // Temporary variables to store input values from file
    int size = NULL;
    int n = NULL;
    vector<int> temp;

    // Reading file to store appropriate values for frame size and reference numbers
    inputFile >> size;
    while (inputFile >> n) {
        temp.push_back(n);
    }
    
    // Creating class object with temporarily stored values from file
    Memory R1(temp, size);

    // Displays data from file for the user
    R1.printReference();



    R1.fifo();

    R1.optimal();

    R1.lru();

    
   
    


}