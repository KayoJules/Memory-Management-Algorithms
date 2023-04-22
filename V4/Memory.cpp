#include "Memory.h"

// TODO:
// FIFO: Add support for 3+ page size - DONE
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


// First-In-First-Out Algorithm
void Memory::fifo() {
    cout << "------FIFO------" << endl;

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        cout << "Insert: " << reference[i] << endl;        //Debugging purposes
        
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
        print();
        cout << "Page faults: " << faults << endl;
    } // eof main fifo loop
    reset();
} // eof fifo


void Memory::optimal() {
    cout << "------OPTIMAL------" << endl;

    vector<int> remaining;
    remaining = reference;

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        cout << "------INSERTING " << reference[i] << " ------" << endl;        //Debugging purposes

        // Checks frame for duplicate value
        if (!isIn(reference[i])) {

            // Places first 3 values into page frame
            if (frame.size() < frameSize) {
                push(reference[i]);
                remaining.erase(remaining.begin());
            }
            else {
                int position = largestDist(remaining);
                replace(position, reference[i]);
                remaining.erase(remaining.begin());
            }

        }
        else {
            remaining.erase(remaining.begin());
        }
        print();
        cout << "Page faults: " << faults << endl;
        printVector(remaining);
    }
    reset();
}

// Returns index/position of the farthest value to be used
int Memory::largestDist(vector<int> remaining) {

    int victim = -1;
    // Look inside current FRAME
    // Find nearest index of each number in frame
    // Since we will replace the number that is not used for longest
    // The function will return the position of the value with the highest relative index

    for (int i = 0; i < frame.size(); i++) {
        auto it = find(remaining.begin(), remaining.end(), frame[i]);

        if (it != remaining.end()) {
            int slot = distance(remaining.begin(), it);

            if (slot > victim) {
                victim = slot;
            }
        }
        else {
            return i;
        }
    }

    auto index = find(frame.begin(), frame.end(), remaining[victim]);
    int position = distance(frame.begin(), index);

    return position;
}

// Least Recently Used Algorithm
void Memory::lru() {
    cout << "------LRU------" << endl;

    map<int, int> distance;

    for (int i = 0; i < reference.size(); i++) {

        if (!isIn(reference[i])) {

            if (frame.size() < frameSize) {
                push(reference[i]);
                distance[i] = i;
            }
            else {
                int position = lruPosition(distance);
                replace(position, reference[i]);
                distance[position] = i;
                cout << "Replaced: " << reference[i] << " at position: " << position << endl;
            }
            
        }
        else {
            auto index = find(frame.begin(), frame.end(), reference[i]);
            int position = std::distance(frame.begin(), index);

            distance[position] = i;
        } // eof if-else

        print();
        cout << "Page faults: " << faults << endl;
    } // eof main loop
    reset();
} // eof of lru function


// Returns index/position of the least recently used value
int Memory::lruPosition(map<int, int> m) {
    vector<int> temp;

    for (auto& Pair : m) {
        temp.push_back(Pair.second);
    }

    auto minimum = min_element(begin(temp), end(temp));
    
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

void Memory::reset() {

    frame.clear();
    faults = 0;
    cout << "------CLEARED------" << endl;
}


