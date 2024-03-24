# CSE 13S-02 Winter 2024

With instructor Kerry Veenstra and TA Jessie Srinivas.

## About

During my course there were 8 total assignments. Each assignment has its own directory, which generally includes a Makefile, testing scripts, a pdf overviewing how to complete the assignment, a design document, and the code!

In earlier assignments, Makefiles were provided to us, but as the course progressed, we were expected to write our own Makefiles.

I wrote all present tests, although I often used the grading pipeline to check my code for correctness.

I also wrote all of the design documents, using a provided template. This was my introduction to both writing design documents, and using LaTeX. I found working through my thoughts before diving into the code to be helpful, although this was not always the process I followed due to time restraints. Using LaTeX presented a learning curve, but I enjoyed working with it and ended up creating my "cheat-sheet" for a different class in LaTeX as well.

### Assignment 0: Writing Tests

Assignment 0 tasked me with writing tests to identify bugs in several faulty calculator programs. I was only provided with binaries of the various implementations, so writing tests to run with the provided runner.sh was the best way to identify any given bug. I wrote a lot of effective tests, but overlooked a few simple edge cases that I should have tested for.

I received an A on this assignment, and definitely learned a lot about bash scripting and working within a terminal.

### Assignment 1: Left, Right, and Center

For Assignment 1, I built a program that would simulate a game of "Left, Right, and Center". The game takes optional input parameters from the user to determine the number of "players" and/or the seed for the pseudo-random number generator to determine the outcome of each dice "roll".

I received a perfect score for this assignment, and learned about control flow, structs, enums, and simple abstraction in C, among some other less prominent concepts.

### Assignment 2: Hangman

Assignment 2, Hangman, provided an introduction to header files, pointers, and a bit more complexity & abstraction. My main function is really tidy, as I was able to abstract a lot of the logic into helper functions. However, I see a lot of nesting in the most essential helper function "handleGuess", which could be cleaned up.

I received an okay grade on this assignment. I built a really well-functioning hangman program (you can confirm for yourself), but the specific requirements of the assignment dictated a very unique handling of the re-prompt behavior, which I struggled to reverse engineer and implement.

### Assignment 3: XD

This assignment tasked me with recreating some of the core functionality offered by XXD. This assignment got me working with command-line arguments, file operations, and using a buffer to read in characters from a file. Types were also more closely considered for this assignment.

bad_xd.c was a challenge to make our code as short as possible, while still meeting all the requisites. To achieve this, I used ternary operators, reduced all safety checks and removed any unecessary characters.

I received a perfect score for this assignment, and had a lot of fun with it.

### Assignment 4: Calc

In assignment 4, I built a scientific calculator. Command line arguments specify whether my custom mathematical operators or C standard functions will be used. Simple calculations such as addition, subtraction, division, modulus and multiplication are computed using Reverse-Polish Notation (RPN), facilitated by an array-based stack implementation. For more complex operations such as square-root, cosine, sine, and tangent, I implemented custom algorithms.
 
I found reading and interpreting input to be the most challenging part of this assignment, but really enjoyed building custom algorithms for trigonometric functions and diving deeper into RPN.

### Assignment 5: Towers

The "Towers" assignment challenged me to leverage various data structures at once to create greater functionality. Given a provided hash function, I built a hash table implementation featuring create, put, get, and destroy functions. An "item" structure was created to hold a key:id pair, and a linked list implementation was built to store the data within each hash-table "bucket". Each data structure was defined within its respective header file, which kept the process of working with them quite straight-forward and clean. 

The final component to this assignment was to build a program called "uniqq", which was supposed to keep track of each unique word presented. However, I did not have enough time to complete this portion during this week.

Although I did not get to build "uniqq", I did learn a great amount about hash-tables, and got some experience working with linked lists in C.

### Assignment 6: Surfin' USA

"Surfin' USA" was a graph-oriented assignment. The ultimate goal was to solve the Traveling-Salesperson (TSP) problem. To achieve this, I built functions in graph.c to build out a graph given a standardized description of the graph. Additionally, this file contains functions to traverse the graph which would be used in the final TSP implementation. A "path" data structure was built on top of another "stack" implementation in order to effectively keep track of the traversed path. Finally, "tsp.c" put everything together: building the inputted graph, then using a recursive algorithm to Depth-First-Search (DFS) into the graph and keep track of the most efficient path.

As I look back on this code, I think forward-defining the helper functions in tsp.c would have helped with the readabilty a lot. That said, I think my DFS implementation is clean and approachable.

I did very well on this assignment, but definitely found the DFS algorithm difficult to get a handle on at first.

### Assignment 7: Huffman Coding

The components for this assignment included: bitreader.c (an object that reads in a file bit by bit), bitwriter.c (an object that writes to a file bit by bit), pq.c- a priority queue implementation, and the meat of the project: huff.c and dehuff.c. 

"huff" reads an input file to build a frequency histogram for each byte. Using this histogram, it constructs a Huffman tree, where each leaf node represents a byte, and the path from the root to a leaf encodes the byte's Huffman code. Next, a table mapping each byte to its Huffman code and code length is filled. The program then writes a compressed version of the input file to the output file, including a header with the original file size and the Huffman tree for decompression. 

"dehuff" reconstructs the Huffman tree by reading encoded tree information from the input file, using a stack to manage the tree nodes. With the tree reconstructed, the code reads the compressed data bit by bit, traverses the Huffman tree according to these bits, and writes the leaf node symbols to the output file until the original file size is reached.

This was definitely a challenging assignment! I am glad to have been introduced to compression algorithms in this way, and feel that this assignment put my C programming skills to a true test.