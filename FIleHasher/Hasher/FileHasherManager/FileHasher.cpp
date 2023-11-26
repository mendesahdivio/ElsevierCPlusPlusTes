
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <memory>
#include "../HasherInterface.cpp"

struct HashingErros {
    const std::string cantOpenFile = "Error opening file: ";
    const std::string cantCreateFile = "Error creating output file : ";
};


class FileHasher {
public:
    FileHasher(std::string filename, std::size_t block_size, std::unique_ptr<HasherInterface> hasher)
        : filename(std::move(filename)), blockSize(block_size), hasher(std::move(hasher)) {}

    void hashFile() {
        std::cout << "this is the file name from the input >> " << filename << std::endl;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::runtime_error(errorStrings.cantOpenFile + filename);
            return;
        }

        std::ofstream output("output.txt"); 

        if (!output.is_open()) {
            std::runtime_error(errorStrings.cantCreateFile + "output.txt");
            return;
        }

        std::vector<char> buffer(blockSize);
        std::vector<std::thread> threads;
        std::cout << "buffer size from input block >> " << buffer.size() << std::endl;

        //for multiple calls and handler mutithreading
        while (file.read(buffer.data(), static_cast<std::streamsize>(blockSize))) {
            std::cout << "read buffere success and also casting block size" << std::endl;
            threads.emplace_back(&FileHasher::hashBlock, this, buffer.data(), blockSize, std::ref(output));
        }

         // Check if the last read was successful, if not, handle the last block separately this prevents repeating if only block existed
        if (!file.eof() && file.gcount() > 0) {
            std::cout << "Handling the last block separately" << std::endl;
            // Process the last block here if needed
            // You can choose to launch a thread for the last block or handle it directly in the main thread
            hashBlock(buffer.data(), file.gcount(), output);
        }

        for (auto& thread : threads) {
            thread.join();
        }

        file.close();
        output.close();
    }

private:
    void hashBlock(const char* data, size_t size, std::ostream& output) const {
        std::string result = hasher->hash(data, size);
        //This mutext helps syncronize writing to a file
        std::lock_guard<std::mutex> lock(fileWritingMutex);
        output << result << std::endl;
        std::cout <<  "this is the output string from the hasher >>> " << result << std::endl;
    }

    std::string filename;
    std::size_t blockSize;
    std::unique_ptr<HasherInterface> hasher;
    mutable std::mutex fileWritingMutex;
    HashingErros errorStrings;
};