#ifndef MEMORY_H_
#define MEMORY_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Memory {

public:

    Memory();
    //Memory(int a, int b, int c);
    Memory(vector<int> input, int size);

    void print();
    void printReference();
    void push(int value);
    void replace(int position, int value);
    void reset();

    void setSize(int n);
    void setReference(vector<int> ref);
    bool isIn(int n);
    //bool isFull();

    void fifo();                             // First in first out
    void optimal();                          // Optimal algorithm
    void lru();                              // Least recently used

    int largestDist(vector<int> m);
    int lruPosition(map<int, int> m);

    void printRemaining(vector<int> n);

private:

    //int* frame = new int[size];
    vector<int> frame;
    vector<int> reference;
    vector<vector<char>> record;

    int frameSize = NULL;
    int faults = 0;
};

#endif