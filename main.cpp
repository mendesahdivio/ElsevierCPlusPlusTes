
#include <iostream>
#include <type_traits>
#include <memory>
#include <limits>
#include <sstream>

//works for long, int, double
class BinaryRepresentaion {
    /*prints the binary representation of the number pointer 
    it can take a double, float and interger
    */ 
    public:
    template <typename NumberType> 
    void printBinaryRepresentaion(const NumberType* numPointer) {
    /*reinterpret_cast<const unsigned char*>(numPointer): casting the pointer numPointer to a pointer of type const unsigned char*/
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(numPointer);
    
    // Calculate the size of the number in bytes
    const int sizeOfNum = sizeof(*numPointer);

    std::cout << "Here is the binary representation of >> " << *numPointer << std::endl;

    // Loop through each byte
    for (int i = sizeOfNum - 1; i >= 0; --i) {
        // Loop through each bit in the byte
        for (int j = 7; j >= 0; --j) {
            // Extract the j-th bit and print it
            std::cout << ((bytes[i] >> j) & 1);
        }

        std::cout << " ";
    }

    std::cout << std::endl;
    }
     
};

 template <typename T>
T getUserInput() {
    T userInput;
    std::cout << "Enter a number: ";

    if (!(std::cin >> userInput)) {
        std::cout << "Invalid input. Please enter a valid number." << std::endl;

        // Clear the error flag and discard any remaining input in the buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Recursive call
        return getUserInput<T>();
    }

    return userInput;
}


int main() {
    
    std::unique_ptr<BinaryRepresentaion> binaryRepresentationPtr = std::make_unique<BinaryRepresentaion>();

    auto userInput = getUserInput<double>();

    binaryRepresentationPtr->printBinaryRepresentaion(&userInput);
    return 0;
}