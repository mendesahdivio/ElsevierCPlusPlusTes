
#include <iostream>
#include "Hasher/HasherInterface.cpp"
#include "Hasher/MD5/MD5Hasher.cpp"
#include "Hasher/FileHasherManager/FileHasher.cpp"
#include "Hasher/FileSystem/FileSystem.cpp"

int main(int argc, char* argv[]) {
    //passing 4 arguments via main
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <block_size> <hash_algorithm>" << std::endl;
        return 1;
    }

    //extracting the arguments
    std::string filename = argv[1];
    std::size_t blockSize = std::stoull(argv[2]);
    std::string hashAlgorithm = argv[3];

    //lowercase the hashAlgoInput
     std::transform(hashAlgorithm.begin(), hashAlgorithm.end(), hashAlgorithm.begin(), [](unsigned char c) {
        return std::tolower(c);
    });


    //TODO: varify the file path if valid
    //MARK: make instance of smartPointer to file system 
    std::unique_ptr<FileSystem> fileValidifier = std::make_unique<FileSystem>(filename, blockSize);


    //MARK: do a system check if fil exist or the user has requested to make a block bigger than the file itsel

    try {
        //the below two func calls throw
        //checks if the file exists
        fileValidifier->doesFileExistInPath();
        
        //checks if the file can be hasehd with the given block size
        fileValidifier->canHashFileWithGivenBlock();


        // continue
        std::unique_ptr<HasherInterface> hasher;

        if (hashAlgorithm == "md5") {
            hasher = std::make_unique<MD5Hasher>();
        } else {
            throw std::runtime_error("Unsupported hash algorithm: " + hashAlgorithm);
            return 1;
        }

        FileHasher fileHasher(filename, blockSize, std::move(hasher));
        fileHasher.hashFile();

    }catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
