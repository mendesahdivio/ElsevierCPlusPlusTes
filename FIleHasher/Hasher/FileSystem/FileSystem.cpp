#include <filesystem>
#include <iostream>
namespace fs = std::__fs::filesystem;

struct FileErrorStrings {
    const std::string fileSizeMismatch = "Error: File size is smaller than the specified block size.";
    const std::string missingFile = "Curent File metioned doesnt exist or its some regular file";
};

class FileSystem {
    public:
    //public constructor
    FileSystem(std::string filePath, std::size_t requestedBlockSize)
    : filePath(filePath), requestedBlockSize(requestedBlockSize)
    {}

    bool doesFileExistInPath() {
        fs::path filePath(this->filePath);

        if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
            throw std::runtime_error(fileErrors.missingFile);
            return false;
        }

        return true;
    }

    bool canHashFileWithGivenBlock() {
          std::uintmax_t fileSize = fs::file_size(filePath);
          std::cout << "File Size: " << fileSize << " bytes" << std::endl;
          if (fileSize < this->requestedBlockSize) {
             throw std::runtime_error(fileErrors.fileSizeMismatch);
            return false;
          }

        return true;
    }

    ~FileSystem() {

    }

    private:
    std::string filePath;
    std::size_t requestedBlockSize;
    FileErrorStrings fileErrors;
};