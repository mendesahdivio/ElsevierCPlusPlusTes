
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

class FileHasher {
public:
    FileHasher(std::string filename, std::size_t block_size, std::unique_ptr<HasherInterface> hasher)
        : filename(std::move(filename)), blockSize(block_size), hasher(std::move(hasher)) {}

    void hashFile() {
        std::cout << "this is the file name from the input >> " << filename << std::endl;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::ofstream output("output.txt"); // Change the output file name as needed
        if (!output.is_open()) {
            std::cerr << "Error creating output file" << std::endl;
            return;
        }

        std::vector<char> buffer(blockSize);
        std::vector<std::thread> threads;

        while (file.read(buffer.data(), static_cast<std::streamsize>(blockSize))) {
            threads.emplace_back(&FileHasher::hashBlock, this, buffer.data(), blockSize, std::ref(output));
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

        std::lock_guard<std::mutex> lock(mutex);
        output << result << std::endl;
        std::cout <<  "this is the output string from the hasher >>> " << result << std::endl;
    }

    std::string filename;
    std::size_t blockSize;
    std::unique_ptr<HasherInterface> hasher;
    mutable std::mutex mutex;
};