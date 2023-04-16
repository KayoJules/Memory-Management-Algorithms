#include "Memory.h"

// TODO:
// Optimal
// LRU


// Default constructor
Memory::Memory() {
    
}

// Parameterized contructor; copies reference string
Memory::Memory(vector<int> input, int size)
{
    reference = input;
    frameSize = size;
}



void Memory::fifo() {

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        cout << "Insert: " << reference[i] << endl;        //Debugging purposes

        // Places first 3 values into page frame
        if(frame.size() < frameSize && !isIn(reference[i])) {
            push(reference[i]);
        }
        // Replaces values in the page frame based; uses i % 3 to determine the slot that will be replaced
        else {
            if (faults % 3 == 0 && !isIn(reference[i])) {
                replace(0, reference[i]);
            }
            else if (faults % 3 == 1 && !isIn(reference[i])) {
                replace(1, reference[i]);
            }
            else if (faults % 3 == 2 && !isIn(reference[i])) {
                replace(2, reference[i]);
            }
        }
        print();
        cout << "Page faults: " << faults << endl;
    }
        
    //cout << "Page faults: " << faults << endl;
    // NOTE: && !isIn(reference[i]) : Checks for numbers already inside the frame and skips the number if true
}


void Memory::optimal() {



}


void Memory::lru() {



}



// Print page frame
void Memory::print() {

    cout << "Frame:\n--" << endl;

    for (int i = 0; i < size(frame); i++) {

        cout << frame[i] << endl;

    }

    cout << "--" << endl;
}

void Memory::printReference() {

    cout << "Reference String: ";
    for (int i = 0; i < reference.size(); i++) {
        cout << reference[i] << " ";
    }

    cout << "\nFrame Size: " << frameSize << endl;
}


// Pushes value onto frame vector and increments page fault count
void Memory::push(int value) { frame.push_back(value); faults++; }
// Replaces value of page frame at set position
void Memory::replace(int position, int value) { frame[position] = value; faults++; }

// Takes in desired frame size or reference values from user input
void Memory::setSize(int n) { frameSize = n; }
void Memory::setReference(vector<int> ref) { reference = ref; }

// Returns true if a value is already held in page frame
bool Memory::isIn(int n) {

    for (int i = 0; i < frame.size(); i++) {
        if (frame[i] == n)
            return true;
    }

    return false;
}



