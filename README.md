# CSE 13S-02 Winter 2024

With instructor Kerry Veenstra and TA Jessie Srinivas.

## About

During my course there were 8 total assignments. Each assignment has its own directory, which generally includes a Makefile, testing scripts, a pdf overviewing how to complete the assignment, a design document, and the code!

In earlier assignments, Makefiles were provided to us, but as the course progressed, we were expected to write our own Makefiles. 

I wrote all present tests, although I often used the grading pipeline to check my code for correctness. 

I also wrote all of the design documents, using a provided template. This was my introduction to both writing design documents, and using LaTeX. I found working through my thoughts before diving into the code to be helpful, although this was not always the process I followed due to time restraints. Using LateX presented a learning curve, but I enjoyed working with it and ended up creating my "cheat-sheet" for a different class in LaTeX as well.

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

In assignment 4, I built a simple "scientific calculator". Command line arguments specify whether my custom mathematical operators or C standard functions will be used. Simple calculations such as addition, subtraction, division, modulus and multiplication are computed using Reverse-Polish Notation (RPN), facilitated by a simple stack implementation. For more complex operations such as square-root, cosine, sine, and tangent, I implemented custom algorithms. 

I found reading and interpreting input to be the most challenging part of this assignment, but really enjoyed building custom algorithms for trigonometric functions and diving deeper into RPN.

### Assignment 5: Towers

### Assignment 6: Surfin' USA

### Assignment 7: Huffman Coding