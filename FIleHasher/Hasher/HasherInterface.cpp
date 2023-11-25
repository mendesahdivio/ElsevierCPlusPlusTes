
#include <iostream>
#include <string>
#ifndef HASHER_INTERFACE_CPP
#define HASHER_INTERFACE_CPP

//this is the interface
class HasherInterface {
public:
    virtual std::string hash(const char* data, size_t size) const = 0;
    virtual ~HasherInterface() {}
};

#endif