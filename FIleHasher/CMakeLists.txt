cmake_minimum_required(VERSION 3.10)
project(FileHasher)

# Find OpenSSL (optional, adjust as needed)
find_package(OpenSSL REQUIRED)

# Add the executable
add_executable(FileHasherProg
    main.cpp
    Hasher/HasherInterface.cpp
    Hasher/MD5/MD5Hasher.cpp
    Hasher/FileHasherManager/FileHasher.cpp
)

# Include directories
target_include_directories(FileHasherProg PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${OPENSSL_INCLUDE_DIR}  # Include OpenSSL (optional)
)

# Link libraries (optional, adjust as needed)
target_link_libraries(FileHasherProg PRIVATE
    ${OPENSSL_CRYPTO_LIBRARY}
)

# Set C++ standard
set_target_properties(FileHasherProg PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)