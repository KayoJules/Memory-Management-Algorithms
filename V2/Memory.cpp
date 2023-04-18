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


// First-In-First-Out Algorithm
void Memory::fifo() {

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
                if (faults % 3 == 0) {
                    replace(0, reference[i]);
                }
                else if (faults % 3 == 1) {
                    replace(1, reference[i]);
                }
                else if (faults % 3 == 2) {
                    replace(2, reference[i]);
                }
            } // eof if-else ladder
        } // eof dupe value check
        print();
        cout << "Page faults: " << faults << endl;
    } // eof main fifo loop
    reset();
} // eof fifo


void Memory::optimal() {

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        cout << "Insert: " << reference[i] << endl;        //Debugging purposes

        // Checks frame for duplicate value
        if (!isIn(reference[i])) {

            // Places first 3 values into page frame
            if (frame.size() < frameSize) {
                push(reference[i]);
            }


            // TODO:
            // Optimal Algorithm


        }
    }
}


// Least Recently Used Algorithm
void Memory::lru() {

    // Map will hold <position, index> 
    // Position will only range from 0 - 2
    // Index will store the time which a number was placed into page frame
    // Value does not need to be stored, because it is compared already
    map<int, int> distance;
    tuple<int, int> temp;

    // Iterating through the entire reference string of numbers
    for (int i = 0; i < reference.size(); i++) {
        cout << "Insert: " << reference[i] << endl;        //Debugging purposes
        

        // Checks frame for duplicate value
        if (!isIn(reference[i])) {

            // Places first 3 values into page frame
            if (frame.size() < frameSize) {
                push(reference[i]);
                distance[i] = i;
            }

            // Checking distance for all values in frame
            for (const auto& Pair : distance) {

                if (Pair.second < get<1>(temp)) {
                    temp = make_tuple(reference[i], i);
                }
            }
            // For the values currently sitting in the frame
            // Find and compare index
            // Replace value with the lowest index (indicating it has not been used recently)

            // Every time it replaces a number, remove the corresponding pair from the distance map
            // Will need 1 temp variable to record pair with lowest index; iterate through map and re-assign value if lower than current

            
        }

        // Records value from reference string to its index
        // Ex. Value 7 and its index, 0, will be added to the map

        // distance[reference[i]] = i;          DEBUGGING

        // The number that is sitting in position[0,1,2] was placing during index[i]
        vector<int>::iterator index;
        index = find(frame.begin(), frame.end(), reference[i]);
        int position = std::distance(frame.begin(), index);
        
        distance[position] = i;
    }

    for (const auto &Pair : distance) {
        cout << "\nTESTING MAP PRINT: " << endl;
        cout << Pair.first << " ";
    }

    print();

    cout << "DISTANCE MAP PRINT" << endl;
    map<int, int>::iterator itr;
    for (itr = distance.begin(); itr != distance.end(); itr++) {
        cout << itr->first << " " << itr->second << endl;
    }
}


// Calculates distance between values in the reference string
int Memory::distance(int n) {

    return 0;
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


