
#include <iostream>
#include "Hasher/HasherInterface.cpp"
#include "Hasher/MD5/MD5Hasher.cpp"
#include "Hasher/FileHasherManager/FileHasher.cpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <block_size> <hash_algorithm>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::size_t block_size = std::stoull(argv[2]);
    std::string hash_algorithm = argv[3];

    std::unique_ptr<HasherInterface> hasher;

    if (hash_algorithm == "md5") {
        hasher = std::make_unique<MD5Hasher>();
    } else {
        std::cerr << "Unsupported hash algorithm: " << hash_algorithm << std::endl;
        return 1;
    }

    FileHasher fileHasher(filename, block_size, std::move(hasher));
    fileHasher.hashFile();

    return 0;
}
