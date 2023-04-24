#include "Memory.h"

// TODO:
// Horizontal Print


// Default constructor
Memory::Memory() {
    
}

// Parameterized contructor; copies reference string
Memory::Memory(vector<int> input, int size)
{
    reference = input;
    frameSize = size;
}


// First-In-First-Out Algorithm
void Memory::fifo() {
    //cout << "---------- FIFO ----------" << endl;
    reset();

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        //cout << "------ Inserting: " << reference[i] << " ------" << endl;
        
        // Checks frame for duplicate value
        if(!isIn(reference[i])) {
        
            // Places first 3 values into page frame
            if (frame.size() < frameSize) {
                push(reference[i]);
            }
            // Replaces values in the page frame based; uses i % 3 to determine the slot that will be replaced
            else {

                int pos = faults % frameSize;
                replace(pos, reference[i]);

            } // eof if-else ladder
        } // eof dupe value check

        //print();
        //cout << "Page faults: " << faults << "\n\n";
        recordFrame();

    } // eof main fifo loop
    cout << "---------- FIFO Summary ----------" << "\n";
    printSummary();
} // eof fifo


void Memory::optimal() {
    //cout << "---------- OPTIMAL ----------" << endl;
    reset();

    // The Remaining vector will hold all values that need to be placed into the frame, and values will be popped off after being processed 
    vector<int> remaining;
    remaining = reference;

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        //cout << "------ Inserting: " << reference[i] << " ------" << endl;

        // Checks frame for duplicate value
        if (!isIn(reference[i])) {

            // Places first 3 values into page frame
            if (frame.size() < frameSize) {
                push(reference[i]);

                // Pop off processed value from the Remaining vector
                remaining.erase(remaining.begin());
            }
            else {
                int position = largestDist(remaining);
                replace(position, reference[i]);
                remaining.erase(remaining.begin());
            }

        }
        // Pops off value if it is already contained in the frame
        else {
            remaining.erase(remaining.begin());
        }
        //print();
        //cout << "Page faults: " << faults << endl;
        //printRemaining(remaining);
        recordFrame();
    }
    cout << "---------- Optimal Summary ----------" << "\n";
    printSummary();
}

// Optimal: Returns index/position of the farthest value to be used by looking at index of remaining numbers to be placed
int Memory::largestDist(vector<int> remaining) {

    int victim = -1;

    // Iterates through all numbers in frame
    for (int i = 0; i < frame.size(); i++) {

        // Locates position of frame's value in the vector of remaining numbers/reference strand
        auto it = find(remaining.begin(), remaining.end(), frame[i]);

        // If index of found number is higher than current recorded high, re-assigned
        if (it != remaining.end()) {
            int slot = distance(remaining.begin(), it);

            if (slot > victim) {
                victim = slot;
            }
        }
        // Returns position of current number immediately not found in remaining numbers
        else {
            return i;
        }
    }

    // Finds position of value to be replaced then returns it
    auto index = find(frame.begin(), frame.end(), remaining[victim]);
    int position = distance(frame.begin(), index);

    return position;
}

// Least Recently Used Algorithm
void Memory::lru() {
    //cout << "---------- LRU ----------" << endl;
    reset();

    // Records current values in frame and their index in relationt to the reference number strand
    map<int, int> distance;

    for (int i = 0; i < reference.size(); i++) {
        //cout << "------ Inserting: " << reference[i] << " ------" << endl;

        if (!isIn(reference[i])) {

            if (frame.size() < frameSize) {
                distance[faults] = i;
                push(reference[i]);
            }
            else {
                int position = lruPosition(distance);
                replace(position, reference[i]);
                distance[position] = i;
            }
            
        }
        else {
            auto index = find(frame.begin(), frame.end(), reference[i]);
            int position = std::distance(frame.begin(), index);
            distance[position] = i;
        } // eof if-else

        //print();
        //cout << "Page faults: " << faults << "\n\n";
        recordFrame();

    } // eof main loop
    cout << "---------- LRU Summary ----------" << "\n";
    printSummary();
} // eof of lru function


// Returns index/position of the least recently used value
int Memory::lruPosition(map<int, int> m) {
    vector<int> temp;

    // Creates temp vector of the indicies of the values in the frame
    for (auto& Pair : m) {
        temp.push_back(Pair.second);
    }

    // Finds element with the lowest index/timestamp, which indicates that it has not been used for the longest
    auto minimum = min_element(begin(temp), end(temp));
    
    // Returns the position of the value to be replaced
    for (auto& Pair : m) {
        if (Pair.second == *minimum) {
            return Pair.first;
        }
    }
}

// Print page frame
void Memory::print() {

    cout << "Frame:\n--" << endl;

    for (int i = 0; i < size(frame); i++) {

        cout << frame[i] << endl;

    }

    cout << "--" << endl;
}

// Prints reference string from input file
void Memory::printReference() {

    cout << "Reference String: ";
    for (int i = 0; i < reference.size(); i++) {
        cout << reference[i] << " ";
    }

    cout << "\nFrame Size: " << frameSize << "\n\n";
}

// Optimal: Prints remaining values to be placed in frame
void Memory::printRemaining(vector<int> n) {

    cout << "Remaining Reference String: ";
    for (int i = 0; i < n.size(); i++) {
        cout << n[i] << " ";
    }
    cout << "\n\n";
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

// Cleans the appropriate resources needed to perform algorithm functions
void Memory::reset() {

    faults = 0;
    frame.clear();
    record.clear();
    summary.clear();

}

// Pushes current state of frame into record vector
void Memory::recordFrame() {

    record.push_back(frame);

}

// Prints all page faults and states of frames for an algorithm
void Memory::printSummary() {

    vector<string> filler(frameSize, "-");

    for (int i = 0; i < record.size(); i++) {
        summary.push_back(filler);
    }

    for (int i = 0; i < record.size(); i++) {
        for (int j = 0; j < record[i].size(); j++) {
            summary[i][j] = to_string(record[i][j]);
        }
    }

    for (int i = 0; i < summary[i].size(); i++) {
        cout << "|";
        for (int j = 0; j < summary.size(); j++) {
            cout << summary[j][i] << "|";
        }
        cout << endl;
    }
    cout << "Page faults: " << faults << "\n";
    cout << "\n\n";
}



