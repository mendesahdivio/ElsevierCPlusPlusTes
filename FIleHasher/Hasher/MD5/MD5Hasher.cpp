
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>
#include "../HasherInterface.cpp"

class MD5Hasher : public HasherInterface {
public:
    std::string hash(const char* data, size_t size) const override {
        MD5_CTX md5Context;
        MD5_Init(&md5Context);
        MD5_Update(&md5Context, data, size);

        unsigned char result[MD5_DIGEST_LENGTH];
        MD5_Final(result, &md5Context);

        std::stringstream ss;
        for (unsigned char byte : result) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }

        return ss.str();
    }
};