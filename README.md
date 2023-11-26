
# ElsevierCPlusPlusTes

This Repository is a test provided by Elsevier company for the role of c++ developer
it contains a set of 3 task 

1. (30 min approximately) Write a function that takes **number pointer** as argument and prints its binary representation.

    - You are forbidden to use standard C++ library (`std::bitset` and any similar methods are not allowed)

    - Please use `std::count` for output

    - You can use std::cout for displaying the output on the screen.

    ### Classes
BinaryRepresentation Class

    The class is designed to work with different numeric types (long, int, double).
    The printBinaryRepresentation member function takes a pointer to a numeric type (NumberType) and prints its binary representation.
    Internally, it uses reinterpret_cast to convert the numeric pointer into a pointer of type const unsigned char*. This allows viewing the binary representation of the numeric value byte by byte.
    The binary representation is printed bit by bit, starting with the most significant bit (MSB) of the last byte.

Functions
getUserInput Function

    This template function prompts the user to enter a number of type T.
    It performs input validation to ensure a valid numeric input.
    If the input is invalid, it clears the error flag, discards the remaining input in the buffer, and recursively calls itself to prompt the user again.
    It returns the validated user input.

main Function

    Creates a std::unique_ptr to an instance of the BinaryRepresentation class.
    Calls getUserInput to get a user-inputted double.
    Invokes the printBinaryRepresentation function of the BinaryRepresentation class to print the binary representation of the entered double.

Usage
    
    Compile the code using a C++ compiler (e.g., g++).
    g++ binary_representation.cpp -o binary_representation
    ./binary_representation


2. (3 hours approximately) Write a console program to generate the hash signature of the specified file. The file name and block size will be passed as an argument. The programme should generate a hash for each block and write them sequentially to the output file.

    - You must use mutli-threading optimizations to make hashing process faster

    - Size of file to hash is less than 4 GB

    - You may use any opensource implementation of MD5 or CRC hashing algorithms as your hash function for a block

    - std library is allowed to use in any way

    - Using any other thirdparty libraries are prohibited excluding above

    - Make an accent on code quality, class naming, interfaces and error handling

    - Use **smart pointers** for holding Hasher class instance


    ## Features

    - Hashing Algorithms: Supports MD5 hashing algorithm.
    - Multi-Threading: Utilizes multi-threading to improve the hashing process.
    - Customizable Block Size: Specify the block size for hashing. 


    ### Prerequisites

    - C++ compiler
    - OpenSSL library


    ### Build commands

    - cd build
    - cmake ..
    - make
    - ./FileHasherProg /Users/ahdiviomendes/Elsevier-TechnicalTest/FIleHasher/someRandom.txt  blockSize  hashingAlgo

    ex:
    - ./FileHasherProg /Users/ahdiviomendes/Elsevier-TechnicalTest/FIleHasher/someRandom.txt  104  md5

    ### Output:
     - File Size: 104 bytes
     - this is the file name from the input >> /Users/ahdiviomendes/Elsevier-TechnicalTest/    FIleHasher/someRandom.txt
     - buffer size from input block >> 104
     - read buffere success and also casting block size
     - this is the output string from the hasher >>> 3860ec0651ed054ba4906278b6de84b7

    



3. (30 min approximately) Describe 3 most confusing errors and failures you've faced during development.


