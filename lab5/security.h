#ifndef SECURITY_H
#define SECURITY_H

#include <array>
#include <cstddef>
#include <string>
#include <vector>


using Bytes = std::vector<unsigned char>;


constexpr std::size_t SALT_SIZE = 16;

constexpr std::size_t HASH_SIZE = 32;


Bytes randomBytes(std::size_t size);


std::array<unsigned char, HASH_SIZE> hashing(
    const std::string& password,
    const std::array<unsigned char, SALT_SIZE>& salt
);


bool compareHash(
    const std::array<unsigned char, HASH_SIZE>& first,
    const std::array<unsigned char, HASH_SIZE>& second
);


Bytes encryptData(const std::string& text);

std::string decryptData(const Bytes& data);

#endif