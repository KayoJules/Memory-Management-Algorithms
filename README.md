# Memory Management


<h2>Memory Class Notes</h2>
Memory class is intended to hold all functions and do all the processing for the FIFO Optimal and LRU algorithms.<br>


<h4>Frame Variable</h4>

`vector<int> frame;` - The main **page frame** of the program. Vector of integers. Needs to hold 3 values for the assignment.<br><br>


<h4>Reference Variable</h4>

`vector<int> reference;` - Vector of integers that holds the reference string. (7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1)<br><br>


<h4>FrameSize Variable</h4>

`int frameSize = NULL;` - Sets the size of the frame. Determined by the top/first in `ReferenceString.txt`. It's set to 3 rn.<br><br>


<h4>Faults Variable</h4>

`int faults = 0;` - Integer variable to track the number of page faults we have.<br><br>

<br>

<h4>Default Constructor</h4>

`Memory();` - Currently does nothing except create a Memory object<br><br>



<h4>Parameterized Constructor</h4>

`Memory(vector<int> input, int size);` - It creates a Memory object. Stores/copies values in the reference string(7, 0, 1, etc.) into the `input` vector. Also assigns int `frameSize` to the desired number the user wants (ex. 3)<br><br>


<h4>Print Function</h4>

`void print();` - Prints the current values inside of the page frame, in a vertical manner<br><br>



<h4>Print Reference Function</h4>

`void printReference();` - Basically prints everything inside of the input file `ReferenceString.txt` for confirmation<br><br>


<h4>Push Function</h4>

`void push(int value);` - Will begin storing values into the `frame` vector. Genrally will only be used 3 times. Use the number you want added to the frame as the parameter variable. To add 7 to the vector, `push(7);`. The function will also increment the variable `faults` to keep track of the number of page faults. <br><br>
**Note**: Vectors are initialized with a length of 0. You must push elements onto the vector to allocate space for every element.<br>
Example: If you want a vector to be 3 spaces long, you will need to run `push()` 3 times. You can only assign values to vectors after you have pushed onto it; syntax is similar to arrays. `frame[1] = 7;`
<br><br>


<h4>Replace Function</h4>

`void replace(int position, int value);` - Replaces a value inside of the page fault(`frame` vector) by taking in the desired position (0, 1, 2) and the number that will replace the one in the frame.<br>
Example: `replace(1, 7)` will place the number 7 into the 2nd slot of the page `frame` vector
<br><br>


<h4>Reset Function</h4>

`reset();` - Cleans out the page frame vector and sets the number of page faults back to 0. Used in-between algorithm calls to prepare everything.<br><br>


<h4>SetSize Function</h4>

`void setSize(int n);` - Forcibly changes the size of page frames. Mainly used if needed for debugging.<br><br>


<h4>SetReference Function</h4>

`void setReference(vector<int> ref);` - Same as above except it changes the reference string (7, 0, 1, 2, 0, etc.) Also just for debugging.<br><br>


<h4>IsIn Function</h4>

`bool isIn(int n);` - Function that returns true if the number you are looking for is already sitting in the page `frame` vector.<br><br>


<h4>Distance Function</h4>

`int distance(int n);` - Tbh idk if we need this function yet so it's blank rn; does nothing. Was intended to return the distance between 2 duplicate numbers inside of the `reference` string vector.<br><br>


<h4>FIFO Function</h4>

`void fifo();` - First-In-First-Out Algorithm<br><br>


<h4>Optimal Function</h4>

`void optimal();` - Optimal Algorithm<br><br>


<h4>LRU Function</h4>

`void lru();` - Least Recently Used Algorithm<br><br>


CSC3391


